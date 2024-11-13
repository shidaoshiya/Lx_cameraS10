--功能: 设置打印信息等级
--参数：[in]print_level 0：info     所有调试信息
--                      1：warn     重要及警告类调试信息
--                      2：error    仅输出错误信息
--      [in]enable_screen_print 是否在窗口打印
--      [in]log_path            log文件保存路径，可以为空，则保存在当前执行路径
print_level=0
enable_screen_print=true
log_path="../testlogpath/"
result = DcSetInfoOutput(print_level,enable_screen_print,log_path)
if stata ~= 0 then
    print("LDcSetInfoOutput.lua run failed.")
    print("DcSetInfoOutput result: "..result)
else
    print("LDcSetInfoOutput.lua run success.")
end