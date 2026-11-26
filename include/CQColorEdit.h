#ifndef CQColorEdit_H
#define CQColorEdit_H

#include <QPushButton>
#include <QLineEdit>
#include <QFrame>

class CQWidgetMenu;

class QHBoxLayout;
class QToolButton;
class QStyleOptionComboBox;
class QColorDialog;

class CQColorEdit : public QFrame {
  Q_OBJECT

  Q_PROPERTY(QColor  color      READ color        WRITE setColor     )
  Q_PROPERTY(QString colorName  READ colorName    WRITE setColorName )
  Q_PROPERTY(bool    editable   READ isEditable   WRITE setEditable  )
  Q_PROPERTY(bool    showSwatch READ isShowSwatch WRITE setShowSwatch)

 public:
  CQColorEdit(QWidget *parent=nullptr);

  //---

  const QColor &color() const { return color_; }
  void setColor(const QColor &color);

  QString colorName() const { return colorName_; }
  void setColorName(const QString &colorName);

  bool isEditable() const { return editable_; }
  void setEditable(bool editable=true);

  bool isShowSwatch() const { return showSwatch_; }
  void setShowSwatch(bool b=true);

  void setNoFocus();

  //---

  QLineEdit *lineEdit() const { return edit_; }

  void paintEvent(QPaintEvent *) override;

  void resizeEvent(QResizeEvent *) override;

 private:
  friend class CQColorEditMenuButton;

  void updateEdit();

  void setNoFocusHier(QWidget *w);

  void emitColorChanged();

  void initStyle(QStyleOptionComboBox &opt);

 private Q_SLOTS:
  void textChangedSlot();

  void buttonSlot();

  void showMenuSlot();
  void hideMenuSlot();

  void colorSlot(const QColor &color);

  void closeMenuSlot();

 Q_SIGNALS:
  void colorChanged(const QColor &color);
  void colorNameChanged(const QString &colorName);

  void menuHidden();

 private:
  bool          editable_   { true };
  bool          showSwatch_ { false };
  QColor        color_;
  QString       colorName_;
  QLineEdit*    edit_       { nullptr }; // text edit
  QPushButton*  button_     { nullptr }; // menu button
  CQWidgetMenu* menu_       { nullptr }; // popup menu
  QColorDialog* colorDlg_   { nullptr }; // dialog for menu
  QToolButton*  swatch_     { nullptr }; // color swatch
};

//---

class CQColorEditEdit : public QLineEdit {
  Q_OBJECT

 public:
  CQColorEditEdit(CQColorEdit *edit);

  void paintEvent(QPaintEvent *) override;

 private:
  CQColorEdit *edit_ { nullptr };
};

//---

class CQColorEditMenuButton : public QPushButton {
  Q_OBJECT

 public:
  CQColorEditMenuButton(CQColorEdit *edit);

  void paintEvent(QPaintEvent *) override;

 private:
  CQColorEdit *edit_ { nullptr };
};

#endif
