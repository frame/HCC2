package main

import (
    "bytes"
    "fmt"
    "io"
    "io/ioutil"
    "mime/multipart"
    "net/http"
    "os"
    "regexp"
    "os/exec"
    "strings"
)

func main() {

    var exportPath string //absolute path without trailing slash
    var exportType string //order|bonus.
    var hccVersion string
    var databaseVersion string
    var profileName string
    var profileShard string

    if len(os.Args) != (4+1) && len(os.Args) != (6+1) {
        fmt.Printf("HCC POD Uploader\n");
        fmt.Printf("Syntax: upload.exe <exportPath> <exportType> <hccVersion> <databaseVersion> [profileName] [profileShard]\n");
        os.Exit(1)
    }
    exportPath = os.Args[1]
    exportType = os.Args[2]
    hccVersion = os.Args[3]
    databaseVersion = os.Args[4]
    if len(os.Args) == (6+1) {
        profileName = os.Args[5]
        profileShard = os.Args[6]
    }

    if (exportType != "order") {
        fmt.Printf("Error: This plugin can only process exportType 'order', not '%s'.\n", exportType);
        os.Exit(1)
    }

    requiredFiles := []string {"order.xml", "report.xml", "report.html"}
	for _, element := range requiredFiles {
        if _, err := os.Stat(exportPath + "/" + element); os.IsNotExist(err) {
            fmt.Printf("Error: Generated order and report files not found: (%s/%s)\n", exportPath, element);
            os.Exit(1)
        }
    }

    client := &http.Client{}
    var remoteURL = "https://hcc.reclamation.dk/pod/submit.php"

    values := make(map[string]io.Reader)
    
    values["type"] = strings.NewReader(exportType)
    values["hcc-version"] = strings.NewReader(hccVersion)
    values["hcc-database"] = strings.NewReader(databaseVersion)
    values["name"] = strings.NewReader(profileName)
    values["shard"] = strings.NewReader(profileShard)
    values["version"] = strings.NewReader("2")
    values["order"] = mustOpen(exportPath + "/order.xml")
    values["report"] = mustOpen(exportPath + "/report.xml")
    values["report_html"] = mustOpen(exportPath + "/report.html")
    if _, err := os.Stat(exportPath + "/profile.xml"); err == nil {
        values["profile"] = mustOpen(exportPath + "/profile.xml")
    }

    res, err := Upload(client, remoteURL, values)
    if err != nil {
        panic(err)
    }
    body, err := ioutil.ReadAll(res.Body)
    if err != nil {
        fmt.Printf("Error: HCC POD Website reported error:\n%s.\n", err);
        os.Exit(1)
    }
    if (res.StatusCode == 200) {
        //fmt.Printf("Reponse:\n%s\n", string(body));
        var re = regexp.MustCompile(`(?s)(^[A-z0-9]{10}$)`)
        if len(re.FindStringIndex(string(body))) > 0 {
            url := "https://hcc.reclamation.dk/pod/?id=" + string(body);
            fmt.Printf("%s\n", url);
            exec.Command("rundll32", "url.dll,FileProtocolHandler", url).Start()
        } else {
            fmt.Printf("Error: HCC POD Website did not repond properly.\n");
            fmt.Printf("Reponse: %s\n", string(body));
            os.Exit(1)
        }
    } else {
        fmt.Printf("Error: HCC POD Website returned on error-code: %d.\n", res.StatusCode);
        os.Exit(1)
    }
}

func Upload(client *http.Client, url string, values map[string]io.Reader) (res *http.Response, err error) {
    var b bytes.Buffer
    w := multipart.NewWriter(&b)
    for key, r := range values {
        var fw io.Writer
        if x, ok := r.(io.Closer); ok {
            defer x.Close()
        }
        // Add files
        if x, ok := r.(*os.File); ok {
            if fw, err = w.CreateFormFile(key, x.Name()); err != nil {
                return
            }
        } else {
            // Add other fields
            if fw, err = w.CreateFormField(key); err != nil {
                return
            }
        }
        if _, err = io.Copy(fw, r); err != nil {
            return
        }

    }
    w.Close()

    req, err := http.NewRequest("POST", url, &b)
    if err != nil {
        return
    }
    req.Header.Set("Content-Type", w.FormDataContentType())

    // Submit the request
    res, err = client.Do(req)
    if err != nil {
        return
    }

    // Check the response
    if res.StatusCode != http.StatusOK {
        err = fmt.Errorf("bad status: %s", res.Status)
    }
    return res, nil
}

func mustOpen(f string) *os.File {
    r, err := os.Open(f)
    if err != nil {
        panic(err)
    }
    return r
}