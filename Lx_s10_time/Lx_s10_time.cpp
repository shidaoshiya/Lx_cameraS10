#include "Lx_s10_time.h"
#include "qdir.h"
#include <qstring.h>
#include <sstream>
#include <fstream>
#include <QMessageBox>
#include <iomanip>
#include <thread> 
#include <chrono>
#include <functional>
Lx_s10_time::Lx_s10_time(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("S10采集原图（时间间隔）");
    connect(ui.pushButton, &QPushButton::clicked, this, [=]() {
        emit startWork();
        });
    LxDeviceInfo* info;
    DcGetDeviceList(&info, &devnum);
    for (int i = 0; i < devnum; i++)
    {
        devList.push_back(*(info + i));
    }
    for (int i = 0; i < devList.size(); i++)
    {
        int open_mode = 0;
        LxDeviceInfo infof;
        std::string param = std::to_string(i);
        DcHandle handle = 0;
        auto dStatus = DcOpenDevice(LX_OPEN_MODE(open_mode), param.c_str(), &handle, &infof);
        auto sStatus = DcStartStream(devList[i].handle);
        std::cout << "device" << i << "open status:" << dStatus << " " << "startStream: " << sStatus << std::endl; 
        std::string raw_file_name = "data";

        raw_file_name.append("/").append(devList[i].id).append("/");

        // MkdirByPath(raw_file_name.c_str());
        MkdirByPath(raw_file_name.c_str());
        std::string save_image_log_path = raw_file_name + "save_img.log";
        save_img_log_.reset(new std::fstream(save_image_log_path.c_str(), std::ios::out | std::ios::in | std::ios::app),
            [](std::fstream* p) { p->close(); });
        *save_img_log_.get() << "name" << "\t" << "laser_temperature " << "\t""tof1_temperature " << std::endl;
    }
   
    connect(this, &Lx_s10_time::startWork, this, &Lx_s10_time::work);
	connect(ui.pushButton_2, &QPushButton::clicked, [=]() {
		isStart = false;
		});
   
}
bool Lx_s10_time::MkdirByPath(const char* path) {
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
bool Lx_s10_time::SaveImage()
{
    auto save_cnt = 0;
    
    while (true)
    {
        if (!isStart)
        {
            continue;
        }
        std::this_thread::sleep_for(std::chrono::seconds(ui.spinBox->value()));

        std::string ssave_cnt = std::to_string(save_cnt);
        for (int i = 0; i < devnum; ++i)
        {
            std::string raw_file_name = "data";

            raw_file_name.append("/").append(devList[i].id).append("/");

           // MkdirByPath(raw_file_name.c_str());
            std::string save_path = raw_file_name + "raw_" + ssave_cnt + ".bin";

            std::string save_image_log_path = raw_file_name + "save_img.log";

            int flag = -99;
            bool flagg = true;
         /*   while (flagg)
            {*/
            std::cout<<DcSetStringValue(devList[i].handle, 4108, save_path.c_str());
        /*        if (flag != 0)
                {
                    continue;
                }        
                else
                {
                    flagg = false;
                }

            }*/
            //DcSetStringValue(devList[i].handle, 4108, save_path.c_str());

            save_img_log_.reset(new std::fstream(save_image_log_path.c_str(), std::ios::out | std::ios::in | std::ios::app),
                [](std::fstream* p) { p->close(); });
            //*save_img_log_.get() << "name" << "\t" << "laser_temperature " << "\t""tof1_temperature " << std::endl;

            LxFloatValueInfo last_tmep = { 0 };
            DcGetFloatValue(devList[i].handle, LX_FLOAT_DEVICE_TEMPERATURE, &last_tmep);
            LxFloatValueInfo tof1_tmep = { 0 };
            DcGetFloatValue(devList[i].handle, 2102, &tof1_tmep); //tof1温度
            *save_img_log_.get() << std::fixed << std::setprecision(2) << save_cnt << "\t" << last_tmep.cur_value << "\t" << "\t" << tof1_tmep.cur_value << std::endl;

            if (devList[i].dev_type == LX_DEVICE_S10)
            {
                auto isPixelDataAllZeros = [](const std::vector<char>& data, int start, int size) -> bool {
                    for (int i = start; i < start + size; ++i) {
                        if (data[i] != 0) {
                            return false;
                        }
                    }
                    return true;
                    };
                const int width = 240;
                const int height = 180;
                constexpr int bytesPerPixel = 32 * 2; //每个像素大小
                constexpr int splitSize = 2 * 2;  // 像素间隔符
                constexpr int imageInfoSize = 4 * 20 * 68 * 2; //结束符
                constexpr int imageDataSize = width * height * (bytesPerPixel * 2 + splitSize * 2);//图像数据大小
                constexpr int totalDataSize = width * height * (bytesPerPixel * 2 + splitSize * 2) + imageInfoSize;//图像文件大小
                std::ifstream file(save_path.c_str(), std::ios::binary);
                std::vector<char> imageData(totalDataSize);
                file.seekg(0, std::ios::end);  // 移动到文件末尾
                file.seekg(0, std::ios::end);  // 移动到文件末尾
                int fsize = static_cast<int>(file.tellg());  // 获取文件大小
                if (fsize != totalDataSize) {
                    file.close();
                    QMessageBox::critical(nullptr, "Error", "image data content size not correct");            
                    return false;
                }

                file.seekg(0, std::ios::beg);  // 若需要重新读取文件内容，重置文件指针到开始位置
                file.read(imageData.data(), totalDataSize);
                file.close();

                // 循环所有像素, 逐一检查每像素的数据部分是否全0
                bool ret = false;
                for (int i = 0; i < imageDataSize; i += (bytesPerPixel + splitSize)) {
                    if (isPixelDataAllZeros(imageData, i, bytesPerPixel) == false) {
                        ret = true;
                        break;
                    }
                }
                if (ret == false) {
                    QMessageBox::critical(nullptr, "Error", "image data content is empty");
                    return false;
                }
            }
            else if (devList[i].dev_type == LX_DEVICE_S10PRO)
            {
                auto isPixelDataAllZeros = [](const std::vector<char>& data, int start, int size) -> bool {
                    for (int i = start; i < start + size; ++i) {
                        if (data[i] != 0) {
                            return false;
                        }
                    }
                    return true;
                    };
                //64bin
                const int width = 240;
                const int height = 180;
                constexpr int bytesPerPixel = 64 * 2; //每个像素大小
                constexpr int splitSize = 4 * 2;  // 像素间隔符
                constexpr int imageInfoSize = 4 * 20 * 68 * 2; //结束符
                constexpr int imageDataSize = width * height * (bytesPerPixel + splitSize);//图像数据大小
                constexpr int totalDataSize = width * height * (bytesPerPixel + splitSize) + imageInfoSize;//图像文件大小
                std::ifstream file(save_path.c_str(), std::ios::binary);
                std::vector<char> imageData(totalDataSize);
                file.seekg(0, std::ios::end);  // 移动到文件末尾
                file.seekg(0, std::ios::end);  // 移动到文件末尾
                int fsize = static_cast<int>(file.tellg());  // 获取文件大小
                if (fsize != totalDataSize) {
                    file.close();
                    QMessageBox::critical(nullptr, "Error", "image data content size not correct");              
                    return false;
                }

                file.seekg(0, std::ios::beg);  // 若需要重新读取文件内容，重置文件指针到开始位置
                file.read(imageData.data(), totalDataSize);
                file.close();

                // 循环所有像素, 逐一检查每像素的数据部分是否全0
                bool ret = false;
                for (int i = 0; i < imageDataSize; i += (bytesPerPixel + splitSize)) {
                    if (isPixelDataAllZeros(imageData, i, bytesPerPixel) == false) {
                        ret = true;
                        break;
                    }
                }
                if (ret == false) {
                    QMessageBox::critical(nullptr, "Error", "image data content is empty");                  
                    return false;
                }
            }
        }
        ++save_cnt;
    }

   
}
void Lx_s10_time::work()
{
    isStart = true;
}
Lx_s10_time::~Lx_s10_time()
{
    for (int i = 0; i < devList.size(); i++)
    {
        auto CStatus = DcCloseDevice(devList[i].handle);
        std::cout << "device" << i << "Close status:" << CStatus << std::endl;
    }
}
