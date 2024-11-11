#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include <string>
#include <vector>
#include "lx_camera_api.h"
#include "ui_Lx_s10_time.h"

class Lx_s10_time : public QMainWindow
{
    Q_OBJECT

public:
    Lx_s10_time(QWidget *parent = nullptr);
    ~Lx_s10_time();
    bool SaveImage();
signals:
    void startWork();
 
private:
    int devnum;
    std::vector< LxDeviceInfo> devList;
    bool MkdirByPath(const char* path);
    bool isFileEmpty(const std::string& filename);
    inline std::string QstrTostr(const QString qstr);
    std::shared_ptr<std::fstream>  save_img_log_ = nullptr;

    bool isStart = false;
public slots:
    void work();

private:
    Ui::Lx_s10_timeClass ui;
};
