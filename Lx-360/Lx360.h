#pragma once


#include <QtWidgets/QMainWindow>
#include "ui_Lx360.h"
#include "livox_lidar_api.h"

#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <chrono>
#include <iostream>

#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>


typedef struct StoreStragey {
    bool isSave = false;
    int value = 0;
    uint32_t interval = 1000;
    uint32_t cur_file_num = 1;
    std::string path = "./data/";
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
}StoreStragey;

class Lx360 : public QMainWindow
{
    Q_OBJECT
private:
    void saveImage();
    bool MkdirByPath(const char* path);
    StoreStragey* stragey = nullptr;   
    int sdkinit(std::string path);
signals:
    void startWork();
public slots:
	void work();
   
public:
    Lx360(QWidget *parent = nullptr);
    ~Lx360();
private:
    Ui::Lx360Class ui;
};
