--功能: 获取API版本号
--参数：[out]version  API版本号，无需外部分配内存
result=DcGetApiVersion()   --result 执行结果
if result ~=0 then
    print("LDcGetApiVersion run failed.")
    print("GetApiVersion: "..result)
else
    print("LDcGetApiVersion run success.")
end