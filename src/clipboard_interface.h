#pragma once
#include <QString>
class IClipboard {
 public:
  virtual void CopyString(const QString&) = 0;
  virtual void CopyFile(const QString&) = 0;
};
