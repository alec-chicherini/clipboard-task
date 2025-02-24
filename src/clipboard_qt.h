#pragma once
#include <clipboard_interface.h>
class ClipboardQt final : public IClipboard {
  void CopyString(const QString&);
  void CopyFile(const QString&);
};