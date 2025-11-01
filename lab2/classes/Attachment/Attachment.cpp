#include "Attachment.h"

Attachment::Attachment(int sizeKb, const string& fileName, const string& url, AttachmentType type) :
    sizeKb_(sizeKb),
    fileName_(fileName),
    url_(url),
    type_(type) {
}

void Attachment::setSizeKb(int sizeKb) {
    sizeKb_ = sizeKb;
}

void Attachment::setFileName(const string& fileName) {
    fileName_ = fileName;
}

void Attachment::setUrl(const string& url) {
    url_ = url;
}

void Attachment::setType(AttachmentType type) {
    type_ = type;
}

int Attachment::getSizeKb() const {
    return sizeKb_;
}

const string& Attachment::getFileName() const {
    return fileName_;
}

const string& Attachment::getUrl() const {
    return url_;
}

AttachmentType Attachment::getType() const {
    return type_;
}

string Attachment::renameFile(const string& newName)
{
    if (newName.empty()) throw InvalidFileFormatException("Имя файла не может быть пустым");
    if (newName == fileName_) throw InvalidFileFormatException("Имя файла уже установлен");

    fileName_ = newName;

    return fileName_;
}
