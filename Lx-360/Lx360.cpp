#include "Lx360.h"
#include <iostream>
#include <QDir>
std::chrono::time_point<std::chrono::steady_clock> last_called;
Lx360::Lx360(QWidget *parent)
    : QMainWindow(parent)
{
    stragey = new StoreStragey();
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr(new pcl::PointCloud<pcl::PointXYZ>);
    stragey->cloud = cloud_ptr;
    std::string path = "config.txt";
    std::cout << "before sdk init " << std::endl;
    sdkinit(path);
    std::cout << "after sdk init " << std::endl;
   

    ui.setupUi(this);
    this->setWindowTitle("Lx360"); 
	connect(ui.pushButton, &QPushButton::clicked, this, &Lx360::startWork);
	connect(this, &Lx360::startWork, this, &Lx360::work);
}

Lx360::~Lx360()
{

}

bool Lx360::MkdirByPath(const char* path)
{
   
    if (path == nullptr) {
        std::cout << "Path is null." << std::endl;
        return false;
    }
    QDir dir;
    QString qpath = QString::fromLocal8Bit(path);
    // 如果路径不存在，则尝试创建
    if (!dir.exists(qpath)) {
        if (!dir.mkpath(qpath)) {
            std::cout << "mkdir[" << path << "] failed!" << std::endl;
            return false;
        }
    }
    return true;
}
void PointCloudCallback(uint32_t handle, const uint8_t dev_type, LivoxLidarEthernetPacket* data, void* client_data) {
    if (data == nullptr || client_data == nullptr) {
        return;
    }
    // 获取当前时间点
   // auto now = std::chrono::system_clock::now();
    //std::chrono::system_clock lastTime = 0;
    StoreStragey* stragey = (StoreStragey*)client_data;
    //printf("point cloud handle: %u, data_num: %d, data_type: %d, length: %d, frame_counter: %d\n",
    //    handle, data->dot_num, data->data_type, data->length, data->frame_cnt);
  
    if (stragey->isSave == true) {
        auto current_time = std::chrono::steady_clock::now();
        if (data->data_type == kLivoxLidarCartesianCoordinateHighData) {
            LivoxLidarCartesianHighRawPoint* p_point_data = (LivoxLidarCartesianHighRawPoint*)data->data;
            for (uint32_t i = 0; i < data->dot_num; i++) {
                pcl::PointXYZ data(p_point_data[i].x, p_point_data[i].y, p_point_data[i].z);
                stragey->cloud->push_back(data);
            }

            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_called);
            if (elapsed.count() >= stragey->value) {
                std::string timestampStr(reinterpret_cast<const char*>(data->timestamp), sizeof(data->timestamp));
                std::string filename = stragey->path + std::to_string(stragey->cur_file_num) + ".pcd";
                pcl::io::savePCDFileBinary(filename, *(stragey->cloud));
               
                stragey->cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
                stragey->cur_file_num++;
                // 更新上一次调用时间
                last_called = current_time;
                //LivoxLidarRemoveCmdObserver();
                stragey->isSave = false;
            }
        }
        else if (data->data_type == kLivoxLidarCartesianCoordinateLowData) {
            LivoxLidarCartesianLowRawPoint* p_point_data = (LivoxLidarCartesianLowRawPoint*)data->data;
            for (uint32_t i = 0; i < data->dot_num; i++) {
                pcl::PointXYZ data(p_point_data[i].x, p_point_data[i].y, p_point_data[i].z);
                stragey->cloud->push_back(data);
            }
        }
    }
}

int Lx360::sdkinit(std::string path) {
    // REQUIRED, to init Livox SDK2
    if (!LivoxLidarSdkInit(path.c_str())) {
        printf("Livox Init Failed\n");
        LivoxLidarSdkUninit();
        return -1;
    }
    SetLivoxLidarPointCloudCallBack(PointCloudCallback,this->stragey);

  
}
void Lx360::saveImage()
{

}
void Lx360::work()
{
	stragey->value = ui.spinBox->value();
    std::string str = "data/";
	MkdirByPath(str.c_str());
    stragey->isSave = true;
    last_called = std::chrono::steady_clock::now();
    std::string path = "config.txt";
}

