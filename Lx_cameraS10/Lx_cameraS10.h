#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Lx_cameraS10.h"
#include <iostream>
#include <string>
#include <vector>
#include "lx_camera_api.h"
#include "opencv2/opencv.hpp"
using namespace cv;
class Lx_cameraS10 : public QMainWindow
{
    Q_OBJECT

public:
    Lx_cameraS10(QWidget* parent = nullptr);
    ~Lx_cameraS10();
signals:
    void startWork();
private:
    int devnum;
    int groupCount = 1;
    int rgb_height = 0;
    int rgb_width = 0;
    int rgb_data_type = LX_DATA_TYPE::LX_DATA_UNSIGNED_CHAR;
    int rgb_channles = 0;
    bool rgb_enable = false;
    void* rgb_data_ptr = nullptr;
    std::vector< LxDeviceInfo> devList;
    bool MkdirByPath(const char* path);
    inline std::string QstrTostr(const QString qstr);
    std::shared_ptr<std::fstream>  save_img_log_ = nullptr;
    bool SaveImage();
    std::vector<int>  index;
private slots:
    void work();
private:
    Ui::Lx_cameraS10Class ui;
};
