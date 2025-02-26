#include <QDebug>
#include <X11/Xlib.h>
#include <clipboard_x11.h>
#include <stdexcept>

void CheckPropName(const Atom& atom,
                   [[maybe_unused]] Display* display = nullptr) {
  if (atom == None) {
    qDebug() << "ОШИБКА: Atom is None. Throw.";
    throw std::logic_error("Atom is None");
  } else {
    // qDebug() << "Atom  name=" << XGetAtomName(display, atom)
    //         << " id =" << atom << "";
  }
}

void ClipboardX11::CopyString(const QString& string_to_send) {
  Display* display;
  display = XOpenDisplay(NULL);
  if (!display) {
    qDebug() << "ОШИБКА! Не удалось открыть Display";
    return;
  }
  XSync(display, 0);
  int screen = DefaultScreen(display);
  Window window_root = RootWindow(display, screen);
  Window window_client =
      XCreateSimpleWindow(display, window_root, 0, 0, -1, -1, 1, 1, 0);

  const Atom kAtomTargets = XInternAtom(display, "TARGETS", False);
  const Atom kAtomClipboard = XInternAtom(display, "CLIPBOARD", False);
  const Atom kAtomUtf8String = XInternAtom(display, "UTF8_STRING", False);
  const Atom kAtomString = XInternAtom(display, "STRING", False);
  const Atom kAtomUtf8String2 =
      XInternAtom(display, "text/plain;charset=utf-8", False);
  const Atom kAtomCompoundText = XInternAtom(display, "COMPOUND_TEXT", False);
  const Atom kAtomXAString = XInternAtom(display, "XA_STRING", False);

  CheckPropName(kAtomTargets);
  CheckPropName(kAtomClipboard);
  CheckPropName(kAtomUtf8String);
  CheckPropName(kAtomString);
  CheckPropName(kAtomUtf8String2);
  CheckPropName(kAtomCompoundText);
  CheckPropName(kAtomXAString);

  XSetSelectionOwner(display, kAtomClipboard, window_client, CurrentTime);
  qDebug() << "Close app. Ctrl+C";
  XEvent event;
  while (true) {
    XNextEvent(display, &event);
    if (event.type == SelectionRequest) {
      const XSelectionRequestEvent* request = &event.xselectionrequest;

      XEvent response = {SelectionNotify};
      response.xselection.property = 0;
      QByteArray byte_array_to_send;
      if (request->target == kAtomTargets) {
        const Atom targets[] = {kAtomTargets,      kAtomUtf8String,
                                kAtomUtf8String2,  kAtomXAString,
                                kAtomCompoundText, kAtomString};

        XChangeProperty(display, request->requestor, request->property, 4, 32,
                        PropModeReplace, (unsigned char*)targets,
                        sizeof(targets) / sizeof(targets[0]));

        response.xselection.property = request->property;
      }

      else if (request->target == kAtomUtf8String ||
               request->target == kAtomUtf8String2 ||
               request->target == kAtomXAString ||
               request->target == kAtomCompoundText ||
               request->target == kAtomString) {
        byte_array_to_send = string_to_send.toUtf8();
      }

      if (byte_array_to_send.size()) {
        XChangeProperty(display, request->requestor, request->property,
                        request->target, 8, PropModeReplace,
                        (unsigned char*)byte_array_to_send.constData(),
                        byte_array_to_send.size());

        response.xselection.property = request->property;
      }

      response.xselection.display = request->display;
      response.xselection.requestor = request->requestor;
      response.xselection.selection = request->selection;
      response.xselection.target = request->target;
      response.xselection.time = request->time;

      if (!XSendEvent(display, request->requestor, 1, 0, &response)) {
        qDebug() << "ОШИБКА! XSendEvent() = null";
      };
      XFlush(display);
    }
  }
}

void ClipboardX11::CopyFile(const QString& file_path_rhs) {
  QString file_path = file_path_rhs;
  Display* display;
  display = XOpenDisplay(NULL);
  if (!display) {
    qDebug() << "ОШИБКА! Не удалось открыть Display";
    return;
  }
  XSync(display, 0);
  int screen = DefaultScreen(display);
  Window window_root = RootWindow(display, screen);
  Window window_client =
      XCreateSimpleWindow(display, window_root, 0, 0, -1, -1, 1, 1, 0);

  const Atom kAtomTargets = XInternAtom(display, "TARGETS", False);
  const Atom kAtomClipboard = XInternAtom(display, "CLIPBOARD", False);
  const Atom kAtomUtf8String = XInternAtom(display, "UTF8_STRING", False);
  const Atom kAtomMultiple = XInternAtom(display, "MULTIPLE", False);
  const Atom kAtomSaveTargets = XInternAtom(display, "SAVE_TARGETS", False);
  const Atom kAtomUtf8String2 =
      XInternAtom(display, "text/plain;charset=utf-8", False);
  const Atom kAtomTextUriList = XInternAtom(display, "text/uri-list", False);
  const Atom kXSpecialGnomeCopiedFiles =
      XInternAtom(display, "x-special/gnome-copied-files", False);

  CheckPropName(kAtomTargets);
  CheckPropName(kAtomClipboard);
  CheckPropName(kAtomUtf8String);
  CheckPropName(kAtomUtf8String2);
  CheckPropName(kAtomTextUriList);
  CheckPropName(kXSpecialGnomeCopiedFiles);
  CheckPropName(kAtomMultiple);
  CheckPropName(kAtomSaveTargets);

  XSetSelectionOwner(display, kAtomClipboard, window_client, CurrentTime);
  qDebug() << "Do not close app untill file in clipboard";
  XEvent event;
  while (true) {
    XNextEvent(display, &event);
    if (event.type == SelectionRequest) {
      const XSelectionRequestEvent* request = &event.xselectionrequest;

      XEvent response = {SelectionNotify};
      response.xselection.property = 0;
      QByteArray byte_array_to_send;
      if (request->target == kAtomTargets) {
        const Atom targets[] = {
            kAtomTargets,     kAtomUtf8String,           kAtomUtf8String2,
            kAtomTextUriList, kXSpecialGnomeCopiedFiles, kAtomMultiple,
            kAtomSaveTargets};

        XChangeProperty(display, request->requestor, request->property, 4, 32,
                        PropModeReplace, (unsigned char*)targets,
                        sizeof(targets) / sizeof(targets[0]));

        response.xselection.property = request->property;
      } else if (request->target == kAtomUtf8String2 ) {
        byte_array_to_send = file_path.toUtf8();
      } else if (request->target == kAtomTextUriList ||
                 request->target == kAtomUtf8String) {
        byte_array_to_send = (file_path.prepend("file://")).toUtf8();
      } else if (request->target == kXSpecialGnomeCopiedFiles) {
        byte_array_to_send =
            (QString("copy\n%1").arg(file_path)).toUtf8();
      } else if (request->target == kAtomMultiple ||
                 request->target == kAtomSaveTargets) {
        // ok and empty
      }

      if (byte_array_to_send.size()) {
        XChangeProperty(display, request->requestor, request->property,
                        request->target, 8, PropModeReplace,
                        (unsigned char*)byte_array_to_send.constData(),
                        byte_array_to_send.size());

        response.xselection.property = request->property;
      }

      response.xselection.display = request->display;
      response.xselection.requestor = request->requestor;
      response.xselection.selection = request->selection;
      response.xselection.target = request->target;
      response.xselection.time = request->time;

      if (!XSendEvent(display, request->requestor, 1, 0, &response)) {
        qDebug() << "ОШИБКА! XSendEvent() = null";
      };
      XFlush(display);
    }
  }
}
