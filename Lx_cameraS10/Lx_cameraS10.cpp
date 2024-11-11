#include "Lx_cameraS10.h"
#include "qdir.h"
#include <qstring.h>
#include <sstream>
#include <fstream>
#include <QMessageBox>
#include <iomanip>

Lx_cameraS10::Lx_cameraS10(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("S10�ɼ�ԭͼ");
    index.assign(100000, 0);
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
        DcGetBoolValue(devList[i].handle, LX_BOOL_ENABLE_2D_STREAM, &rgb_enable);
        auto rStatus = DcSetBoolValue(devList[i].handle, LX_BOOL_ENABLE_2D_STREAM, true);
        std::cout << "device" << i << "open status:" << rStatus << " " << "rgbStream: " << sStatus << std::endl;
    }
    connect(this, &Lx_cameraS10::startWork, this, &Lx_cameraS10::work);
}
bool Lx_cameraS10::MkdirByPath(const char* path) {
    if (path == nullptr) {
        std::cout << "Path is null." << std::endl;
        return false;
    }
    QDir dir;
    QString qpath = QString::fromLocal8Bit(path);
    // ���·�������ڣ����Դ���
    if (!dir.exists(qpath)) {
        if (!dir.mkpath(qpath)) {
            std::cout << "mkdir[" << path << "] failed!" << std::endl;
            return false;
        }
    }
    return true;
}
bool  Lx_cameraS10::SaveImage()
{
    auto save_cnt = 0;
    while (save_cnt < ui.spinBox->value())
    {
        std::string ssave_cnt = std::to_string(save_cnt);
        for (int i = 0; i < devnum; ++i)
        {

            LxIntValueInfo int_value;
            DcGetIntValue(devList[i].handle, LX_INT_2D_IMAGE_WIDTH, &int_value);
            rgb_width = int_value.cur_value;
            DcGetIntValue(devList[i].handle, LX_INT_2D_IMAGE_HEIGHT, &int_value);
            rgb_height = int_value.cur_value;
            DcGetIntValue(devList[i].handle, LX_INT_2D_IMAGE_CHANNEL, &int_value);
            rgb_channles = int_value.cur_value;
            DcGetIntValue(devList[i].handle, LX_INT_2D_IMAGE_DATA_TYPE, &int_value);
            rgb_data_type = int_value.cur_value;
            bool flag = true;
            while (flag)
            {
                auto ret = DcSetCmd(devList[i].handle, LX_CMD_GET_NEW_FRAME);
                if (LX_SUCCESS != DcGetPtrValue(devList[i].handle, LX_PTR_2D_IMAGE_DATA, &rgb_data_ptr))
                {
                    std::cout << "DcGetPtrValue failed" << std::endl;
                }
                else
                {
                    flag = false;
                }
            }
            cv::Mat rgb_show = cv::Mat(rgb_height, rgb_width, CV_MAKETYPE(rgb_data_type, rgb_channles), rgb_data_ptr);
            if (rgb_show.empty()) {
                QMessageBox::critical(this, "����", "��ǰ���rgb����Ϊ��");
            }

            std::string raw_file_name = "data/";
            std::string raw_file_namef = std::to_string(groupCount);
            raw_file_name.append("/").append(devList[i].id).append("/").append(raw_file_namef);

            MkdirByPath(raw_file_name.c_str());
            std::string save_path = raw_file_name + "/" + "raw_" + ssave_cnt + ".bin";
            std::string save_rgb_path = raw_file_name + "/" + "rgb_" + ssave_cnt + ".png";
            std::string save_image_log_path = raw_file_name + "/" + "save_img.log";
            std::cout << DcSetStringValue(devList[i].handle, 4108, save_path.c_str());            
            cv::imwrite(save_rgb_path, rgb_show);
            if (index[groupCount] == 0)
            {
                index[groupCount] = 1;
                save_img_log_.reset(new std::fstream(save_image_log_path.c_str(), std::ios::out | std::ios::in | std::ios::app),
                    [](std::fstream* p) { p->close(); });
                *save_img_log_.get() << "name" << "\t" << "laser_temperature " << "\t""tof1_temperature " << std::endl;
            }

            LxFloatValueInfo last_tmep = { 0 };
            DcGetFloatValue(devList[i].handle, LX_FLOAT_DEVICE_TEMPERATURE, &last_tmep);
            LxFloatValueInfo tof1_tmep = { 0 };
            DcGetFloatValue(devList[i].handle, 2102, &tof1_tmep); //tof1�¶�
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
                constexpr int bytesPerPixel = 32 * 2; //ÿ�����ش�С
                constexpr int splitSize = 2 * 2;  // ���ؼ����
                constexpr int imageInfoSize = 4 * 20 * 68 * 2; //������
                constexpr int imageDataSize = width * height * (bytesPerPixel * 2 + splitSize * 2);//ͼ�����ݴ�С
                constexpr int totalDataSize = width * height * (bytesPerPixel * 2 + splitSize * 2) + imageInfoSize;//ͼ���ļ���С
                std::ifstream file(save_path.c_str(), std::ios::binary);
                std::vector<char> imageData(totalDataSize);
                file.seekg(0, std::ios::end);  // �ƶ����ļ�ĩβ
                file.seekg(0, std::ios::end);  // �ƶ����ļ�ĩβ
                int fsize = static_cast<int>(file.tellg());  // ��ȡ�ļ���С
                if (fsize != totalDataSize) {
                    file.close();
                    QMessageBox::critical(nullptr, "Error", "image data content size not correct");
                    ++groupCount;
                    return  false;
                }

                file.seekg(0, std::ios::beg);  // ����Ҫ���¶�ȡ�ļ����ݣ������ļ�ָ�뵽��ʼλ��
                file.read(imageData.data(), totalDataSize);
                file.close();

                // ѭ����������, ��һ���ÿ���ص����ݲ����Ƿ�ȫ0
                bool ret = false;
                for (int i = 0; i < imageDataSize; i += (bytesPerPixel + splitSize)) {
                    if (isPixelDataAllZeros(imageData, i, bytesPerPixel) == false) {
                        ret = true;
                        break;
                    }
                }
                if (ret == false) {
                    QMessageBox::critical(nullptr, "Error", "image data content is empty");
                    ++groupCount;
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
                constexpr int bytesPerPixel = 64 * 2; //ÿ�����ش�С
                constexpr int splitSize = 4 * 2;  // ���ؼ����
                constexpr int imageInfoSize = 4 * 20 * 68 * 2; //������
                constexpr int imageDataSize = width * height * (bytesPerPixel + splitSize);//ͼ�����ݴ�С
                constexpr int totalDataSize = width * height * (bytesPerPixel + splitSize) + imageInfoSize;//ͼ���ļ���С
                std::ifstream file(save_path.c_str(), std::ios::binary);
                std::vector<char> imageData(totalDataSize);
                file.seekg(0, std::ios::end);  // �ƶ����ļ�ĩβ
                file.seekg(0, std::ios::end);  // �ƶ����ļ�ĩβ
                int fsize = static_cast<int>(file.tellg());  // ��ȡ�ļ���С
                if (fsize != totalDataSize) {
                    file.close();
                    QMessageBox::critical(nullptr, "Error", "image data content size not correct");
                    ++groupCount;
                    return  false;
                }

                file.seekg(0, std::ios::beg);  // ����Ҫ���¶�ȡ�ļ����ݣ������ļ�ָ�뵽��ʼλ��
                file.read(imageData.data(), totalDataSize);
                file.close();

                // ѭ����������, ��һ���ÿ���ص����ݲ����Ƿ�ȫ0
                bool ret = false;
                for (int i = 0; i < imageDataSize; i += (bytesPerPixel + splitSize)) {
                    if (isPixelDataAllZeros(imageData, i, bytesPerPixel) == false) {
                        ret = true;
                        break;
                    }
                }
                if (ret == false) {
                    QMessageBox::critical(nullptr, "Error", "image data content is empty");
                    ++groupCount;
                    return false;
                }
            }
        }
        ++save_cnt;
    }
    if (ui.spinBox->value() != 0)
    {
        ++groupCount;
        return true;
    }

}
inline std::string Lx_cameraS10::QstrTostr(const QString qstr) {
    QByteArray cdata = qstr.toLocal8Bit();
    return std::string(cdata);
}
void Lx_cameraS10::work()
{
    auto result = SaveImage();
    if (result)
    {
        QMessageBox::information(nullptr, "Success", "Save image success");
    }
    else
    {
        QMessageBox::critical(nullptr, "Error", "Save image failed");
    }
}
Lx_cameraS10::~Lx_cameraS10()
{
    for (int i = 0; i < devList.size(); i++)
    {
        auto CStatus = DcCloseDevice(devList[i].handle);
        std::cout << "device" << i << "Close status:" << CStatus << std::endl;
    }
}