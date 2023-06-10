Function sendHttpPost(posturl,params)
    Dim http
    Set http = CreateObject("MSXML2.ServerXMLHTTP")
    http.Open "POST",posturl,False
    http.setRequestHeader "Content-type","application/x-www-form-urlencoded; charset=UTF-8"
    http.Send(params)
    If http.Status = "200" Then
        sendHttpPost = http.responseText
    Else
        sendHttpPost = http.Status
    End If
    Set http = nothing
End Function

Function URLEncode(strURL)
    Dim I
    For I = 1 To Len(strURL)
        If (Asc(Mid(strURL, I, 1)) >= 48 And Asc(Mid(strURL, I, 1)) <= 57) Or (Asc(Mid(strURL, I, 1)) >= 65 And Asc(Mid(strURL, I, 1)) <= 90) Or (Asc(Mid(strURL, I, 1)) >= 97 And Asc(Mid(strURL, I, 1)) <= 122) Or (Mid(strURL, I, 1) = "-") Or (Mid(strURL, I, 1) = "_") Or (Mid(strURL, I, 1) = ".") Or (Mid(strURL, I, 1) = "~") Then
            URLEncode = URLEncode & Mid(strURL, I, 1)
        ElseIf Mid(strURL, I, 1) = " " Then
            URLEncode = URLEncode & "+"
        Else
            URLEncode = URLEncode & "%" & Right("00" & Cstr(Hex(Asc(Mid(strURL, I, 1)))),2)
        End If
    Next
    Set I = nothing
End Function

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

MsgBox sendHttpPost("https://tool.runoob.com/compile2.php","code=" & URLEncode(readFile(InputBox("CODE file path:"))) & "&token=b6365362a90ac2ac7098ba52c13e352b&stdin=" & URLEncode(readFile(InputBox("INPUT file path:"))) & "&language=7&fileext=cpp"),,"Result in json"
