#pragma once
#include "InvalidFileFormatException.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum class AttachmentType { DOCX, PDF, TXT, XML, PPTX };

class Attachment {
public:
    Attachment(int sizeKb, const string& fileName, const string& url, AttachmentType type);

    void setSizeKb(int sizeKb);
    void setFileName(const string& fileName);
    void setUrl(const string& url);
    void setType(AttachmentType type);

    int getSizeKb() const;
    const string& getFileName() const;
    const string& getUrl() const;
    AttachmentType getType() const;

    string renameFile(const string& newName);
private:
    int sizeKb_;
    string fileName_;
    string url_;
    AttachmentType type_;
};
