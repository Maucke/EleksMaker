dim fso,f,s
dim name
'set ws=createobject("wscript.shell")
'ws.run("Synthesis.bat")
'wscript.sleep 1000
name=inputbox("请在此输入image的名字","提示")
set fso = CreateObject("Scripting.FileSystemObject")
set f = fso.OpenTextFile("Synthesis.c")

s=replace(f.readall,"const", "//const")
s=replace(s,"};", "")

f.close

set r=fso.opentextfile(name&".h",2,true)

r.write "const uint8_t image_"&name&"[][] = {" & Chr(13) & Chr(10) & s &"};"

r.close