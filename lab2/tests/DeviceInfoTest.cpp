#include <gtest/gtest.h>
#include "DeviceInfo.h"
#include <sstream>
#include <regex>
#include <thread>
#include <chrono>

using namespace std;

class DeviceInfoTest : public ::testing::Test {
protected:
    DeviceInfo* device;

    void SetUp() override {
        device = new DeviceInfo("user123", "dev456", "Windows 11", "192.168.0.1", "10.10.2024 12:00:00", DeviceType::DESKTOP);
    }

    void TearDown() override {
        delete device;
    }
};

TEST_F(DeviceInfoTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(device->getUserId(), "user123");
    EXPECT_EQ(device->getDeviceId(), "dev456");
    EXPECT_EQ(device->getOs(), "Windows 11");
    EXPECT_EQ(device->getIpAddress(), "192.168.0.1");
    EXPECT_EQ(device->getLastActive(), "10.10.2024 12:00:00");
    EXPECT_EQ(device->getDeviceType(), DeviceType::DESKTOP);
}

TEST_F(DeviceInfoTest, SettersChangeValuesCorrectly) {
    device->setUserId("newUser");
    device->setDeviceId("newDev");
    device->setOs("Android 14");
    device->setIpAddress("10.0.0.2");
    device->setLastActive("11.11.2024 11:11:11");
    device->setDeviceType(DeviceType::MOBILE);

    EXPECT_EQ(device->getUserId(), "newUser");
    EXPECT_EQ(device->getDeviceId(), "newDev");
    EXPECT_EQ(device->getOs(), "Android 14");
    EXPECT_EQ(device->getIpAddress(), "10.0.0.2");
    EXPECT_EQ(device->getLastActive(), "11.11.2024 11:11:11");
    EXPECT_EQ(device->getDeviceType(), DeviceType::MOBILE);
}

TEST_F(DeviceInfoTest, DetectDeviceTypeDetectsMobile) {
    device->setOs("Android 14");

    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

    device->detectDeviceType();
    cout.rdbuf(oldCout);

    EXPECT_EQ(device->getDeviceType(), DeviceType::MOBILE);
    EXPECT_NE(buffer.str().find("Мобильное"), string::npos);
}

TEST_F(DeviceInfoTest, DetectDeviceTypeDetectsTablet) {
    device->setOs("iPadOS 17");

    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

    device->detectDeviceType();
    cout.rdbuf(oldCout);

    EXPECT_EQ(device->getDeviceType(), DeviceType::TABLET);
    EXPECT_NE(buffer.str().find("Планшет"), string::npos);
}

TEST_F(DeviceInfoTest, DetectDeviceTypeDetectsDesktop) {
    device->setOs("Linux Mint");

    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

    device->detectDeviceType();
    cout.rdbuf(oldCout);

    EXPECT_EQ(device->getDeviceType(), DeviceType::DESKTOP);
    EXPECT_NE(buffer.str().find("Десктоп"), string::npos);
}

TEST_F(DeviceInfoTest, DetectDeviceTypeHandlesEmptyOS) {
    device->setOs("");

    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

    device->detectDeviceType();
    cout.rdbuf(oldCout);

    EXPECT_NE(buffer.str().find("пуста"), string::npos);
}

TEST_F(DeviceInfoTest, UpdateLastActiveChangesDateToCurrent) {
    string before = device->getLastActive();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    device->updateLastActive();

    string after = device->getLastActive();
    EXPECT_NE(before, after);
    EXPECT_FALSE(after.empty());
    EXPECT_NE(after.find("."), string::npos);
}

TEST_F(DeviceInfoTest, ValidateIPAddressAcceptsValidIP) {
    device->setIpAddress("192.168.1.100");
    device->validateIPAddress();

    EXPECT_EQ(device->getIpAddress(), "192.168.1.100");
}

TEST_F(DeviceInfoTest, ValidateIPAddressIgnoresInvalidIP) {
    device->setIpAddress("999.888.777.666");
    device->validateIPAddress();

    EXPECT_EQ(device->getIpAddress(), "999.888.777.666");
}
