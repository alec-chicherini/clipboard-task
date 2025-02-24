#pragma once
#include <clipboard_interface.h>
class ClipboardXcb final : public IClipboard {
  void CopyString(const QString&);
  void CopyFile(const QString&);
};