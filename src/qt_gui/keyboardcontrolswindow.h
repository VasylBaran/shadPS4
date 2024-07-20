#ifndef KEYBOARDCONTROLSWINDOW_H
#define KEYBOARDCONTROLSWINDOW_H

#include <QMainWindow>
#include <QKeySequenceEdit>
#include <QDialog>
#include <QSettings>

#include "input/keys_constants.h"
#include <SDL3/SDL_keycode.h>

#include <QMap>

typedef QMap<Uint32, KeysMapping> QKeyBindingsQMap;
Q_DECLARE_METATYPE(QKeyBindingsQMap)

QT_BEGIN_NAMESPACE
namespace Ui {
class KeyboardControlsWindow;
}
QT_END_NAMESPACE

class KeyboardControlsWindow : public QDialog
{
    Q_OBJECT

public:
    KeyboardControlsWindow(QWidget *parent = nullptr);
    ~KeyboardControlsWindow();

    std::map<Uint32, KeysMapping> getKeysMapping();

private slots:
    void onEditingFinished();

private:
    void validateAndSaveKeyBindings();
    SDL_Keycode convertQtKeyToSDL(Qt::Key qtKey);
    Qt::Key convertSDLKeyToQt(SDL_Keycode qtKey);

    Ui::KeyboardControlsWindow *ui;
    QSet<QKeySequenceEdit*> m_listOfKeySequenceEdits;
    std::map<Uint32, KeysMapping> m_keysMap;
    std::map<KeysMapping, Uint32> m_reverseKeysMap;
    QSettings m_settings;
};
#endif // KEYBOARDCONTROLSWINDOW_H
