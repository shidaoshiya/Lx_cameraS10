is_enable=true   --默认开启
result=DcGetGpuEnable(is_enable)
if result ~= 0 then
    print("LDcGetGpuEnable.lua run failed.")
    print("DcGetGpuEnable result: "..result)
else
    print("LDcGetGpuEnable.lua run success.")
end
print("is_enable: "..tostring(is_enable))