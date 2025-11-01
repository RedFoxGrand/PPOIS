#include <gtest/gtest.h>
#include "Attachment.h"

using namespace std;

class AttachmentTest : public ::testing::Test {
protected:
    Attachment* attachment;

    void SetUp() override {
        attachment = new Attachment(2048, "report.pdf", "https://example.com/report.pdf", AttachmentType::PDF);
    }

    void TearDown() override {
        delete attachment;
    }
};

TEST_F(AttachmentTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(attachment->getSizeKb(), 2048);
    EXPECT_EQ(attachment->getFileName(), "report.pdf");
    EXPECT_EQ(attachment->getUrl(), "https://example.com/report.pdf");
    EXPECT_EQ(attachment->getType(), AttachmentType::PDF);
}

TEST_F(AttachmentTest, SettersWorkCorrectly) {
    attachment->setSizeKb(4096);
    attachment->setFileName("new_doc.docx");
    attachment->setUrl("https://example.com/new_doc.docx");
    attachment->setType(AttachmentType::DOCX);

    EXPECT_EQ(attachment->getSizeKb(), 4096);
    EXPECT_EQ(attachment->getFileName(), "new_doc.docx");
    EXPECT_EQ(attachment->getUrl(), "https://example.com/new_doc.docx");
    EXPECT_EQ(attachment->getType(), AttachmentType::DOCX);
}

TEST_F(AttachmentTest, RenameFileChangesFileName) {
    string newName = "updated_report.pdf";
    string result = attachment->renameFile(newName);

    EXPECT_EQ(result, newName);
    EXPECT_EQ(attachment->getFileName(), newName);
}

TEST_F(AttachmentTest, RenameFileThrowsWhenEmptyName) {
    EXPECT_THROW({
        attachment->renameFile("");
        }, InvalidFileFormatException);
}

TEST_F(AttachmentTest, RenameFileThrowsWhenSameName) {
    EXPECT_THROW({
        attachment->renameFile("report.pdf");
        }, InvalidFileFormatException);
}

TEST_F(AttachmentTest, RenameFileReturnsNewName) {
    string newName = "presentation.pptx";
    EXPECT_EQ(attachment->renameFile(newName), "presentation.pptx");
}
