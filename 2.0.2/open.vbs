Function readFile(path)
    Dim fobj,ftxt
    Set fobj = CreateObject("Scripting.FileSystemObject")
    If fobj.FileExists(path) Then
        Set ftxt = fobj.OpenTextFile(path, 1, false)
        readFile = ftxt.readAll()
    Else
        If MsgBox("File does not exist!",5) = 4 Then
            readFile = readFile(InputBox("Again:"))
        Else
            readFile = ""
        End If
    End If
    Set fobj = nothing
    Set ftxt = nothing
End Function

Function writeFile(path,text)
    Dim fobj,fle
    Set fobj = CreateObject("Scripting.FileSystemObject")
    set fle = fobj.CreateTextFile(path,true)
    fle.Write(text)
    fle.Close()
    Set fobj = nothing
    Set fle = nothing
End Function

writeFile CreateObject("Scripting.FileSystemObject").GetFolder(".").Path & "\connect.txt",readFile(InputBox("Open file address:"))