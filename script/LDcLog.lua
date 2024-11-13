--功能: 允许用户输出调试信息到log文件
--参数：[in]str     要输出的字符串，'\0'结尾
message="This is a test message"
result=DcLog(message)   --执行结果
if result ~= 0 then
    print("LDcLog.log run failed.")
    print("result: "..result)
else
    print("LDcLog.log run success.")
end