#include "wlappersetter.h"
WlapperSetter::WlapperSetter(){

}
bool WlapperSetter::setWallpaper(const QString &imagePath) {
    try {
        std::wstring path = imagePath.toStdWString();

        BOOL result = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, static_cast<void*>(const_cast<wchar_t*>(path.c_str())),
                                            SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
        if (!result) {
            throw WSExeptions("Failed to set wallpaper. Error: " + QString::number(GetLastError()));
        }

        return true;
    } catch (const WSExeptions& ex) {
        qDebug() << "Error:" << ex.getMessage();
    } catch (const QException& ex) {
        qDebug() << "Unexpected error:" << ex.what();
    }

    return false;
}
