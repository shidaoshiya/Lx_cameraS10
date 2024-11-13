is_enable=true
result=DcSetGpuEnable(is_enable)
if result ~= 0 then
    print("LDcSetGpuEnable.lua run failed.")
    print("DcSetGpuEnable result: "..result)
else
    print("LDcSetGpuEnable.lua run success.")
end