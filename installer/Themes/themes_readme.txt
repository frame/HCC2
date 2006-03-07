HOW-TO create custom themes
---------------------------

1. Make a copy of desktop_bright_default.xml and rename it to desktop_bright_{THEME_TITLE}.xml
{THEME_TITLE} will be the name of your new theme. Avoid using spaces.

examples: desktop_bright_pink.xml, desktop_bright_fantasy.xml for bright windows themes (common) or desktop_dark_brick.xml for dark themes (rare).

2. Edit your new file within notepad or any XML-editor (HTML editors also work great to help you set the colors)
3. Remove the two <!-- comments --> lines and insert your Name <author>{YOUR_NAME}</author>.
4. Save.
5. Withing HCC select Options/Settings/Configuration and pick your new theme.


Hints
---------------------------

- Never make changes to any of the default themes - they will be overwritten at each update!

- Once you have selected your new theme you can edit it while running HCC, you can reload the theme from harddisk by hitting CTRL-ALT-R or selecting Options/Settings/Refresh Theme. Please note that some elements require HCC to restart or to make a selection (select different Formula, Technique)

- Colors are either:
windows system colors (COLOR_WINDOWTEXT, COLOR_WINDOW, COLOR_3DLIGHT)
or html hex-colors in RGB (#FFCC00, #F5F5F5)

- For system colors please refer to:
http://msdn.microsoft.com/library/default.asp?url=/library/en-us/sysinfo/base/getsyscolor.asp

- Test your theme on multiple Windows colors themes eg. XP: Silver or some dark one such as Classic: Brick.


Happy Theming..


--
readme v1.2 2007-09-19 16:18