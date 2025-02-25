#pragma once
#include <clipboard_interface.h>
class ClipboardX11 final : public IClipboard {
  void CopyString(const QString&);
  void CopyFile(const QString&);
};