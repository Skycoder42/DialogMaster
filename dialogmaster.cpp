#include "dialogmaster.h"
#include <QCoreApplication>
#include <QProgressDialog>
#include <QProgressBar>

class CloseFilter : public QObject
{
public:
	inline CloseFilter(QObject *parent) :
		QObject(parent)
	{}
	inline bool eventFilter(QObject *, QEvent *ev) Q_DECL_OVERRIDE {
		if(ev->type() == QEvent::Close) {
			ev->ignore();
			return true;
		} else
			return false;
	}
};

bool DialogMaster::TitleAsWindowTitle = false;

void DialogMaster::masterDialog(QDialog *dialog, bool fixedSize, Qt::WindowFlags additionalFlags)
{
	Qt::WindowFlags flags = (fixedSize ? Qt::MSWindowsFixedSizeDialogHint : Qt::Window) | additionalFlags;
	dialog->setSizeGripEnabled(!fixedSize);
	if(dialog->parentWidget()) {
		dialog->setWindowModality(Qt::WindowModal);
		flags |= Qt::Sheet;
	} else {
		dialog->setWindowModality(Qt::ApplicationModal);
		flags |= Qt::Dialog;
	}
	dialog->setWindowFlags(flags);
}

QMessageBox::StandardButton DialogMaster::msgBox(QWidget *parent, DialogMaster::MessageBoxIcon icon, const QString &text, const QString &title, const QString &windowTitle, const QString &details, bool *checked, const QString &checkString, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton, QMessageBox::StandardButton escapeButton)
{
	QMessageBox msgBox(parent);
	if(icon.isCustom)
		msgBox.setIconPixmap(icon.custIcon);
	else
		msgBox.setIcon(icon.mbxIcon);
	msgBox.setWindowTitle(DialogMaster::TitleAsWindowTitle ? title : windowTitle);
	if(DialogMaster::TitleAsWindowTitle || title.isEmpty())
		msgBox.setText(text);
	else {
		msgBox.setText(QStringLiteral("<b>%1</b>").arg(title));
		msgBox.setInformativeText(text);
	}
	if(checked) {
		QCheckBox *box = new QCheckBox(checkString, &msgBox);
		box->setChecked(*checked);
		QObject::connect(box, &QCheckBox::toggled, &msgBox, [checked](bool isChecked){
			*checked = isChecked;
		});
		msgBox.setCheckBox(box);
	}
	msgBox.setStandardButtons(buttons);
	msgBox.setDefaultButton(defaultButton);
	msgBox.setEscapeButton(escapeButton);
	msgBox.setDetailedText(details);

#ifdef Q_OS_WINCE
	Qt::WindowFlags flags = DialogMaster::DefaultFlags;
	if(buttons.testFlag(QMessageBox::Ok))
		flags |= Qt::WindowOkButtonHint;
	if(buttons.testFlag(QMessageBox::Cancel))
		flags |= Qt::WindowCancelButtonHint;
	DialogMaster::masterDialog(&msgBox, true, flags);
#else
	DialogMaster::masterDialog(&msgBox, true);
#endif

	return (QMessageBox::StandardButton)msgBox.exec();
}

QMessageBox::StandardButton DialogMaster::information(QWidget *parent, const QString &text, const QString &title, const QString &windowTitle, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton, QMessageBox::StandardButton escapeButton)
{
	return msgBox(parent,
				  QMessageBox::Information,
				  text,
				  title,
				  windowTitle.isEmpty() ? QCoreApplication::translate("DialogMaster", "Information") : windowTitle,
				  QString(),
				  NULL,
				  QString(),
				  buttons,
				  defaultButton,
				  escapeButton);
}

QMessageBox::StandardButton DialogMaster::information(QWidget *parent, const QString &text, const QString &title, const QString &windowTitle, QMessageBox::StandardButton button1, QMessageBox::StandardButton button2)
{
	return msgBox(parent,
				  QMessageBox::Information,
				  text,
				  title,
				  windowTitle.isEmpty() ? QCoreApplication::translate("DialogMaster", "Information") : windowTitle,
				  QString(),
				  NULL,
				  QString(),
				  button1 | button2,
				  button1,
				  button2);
}

QMessageBox::StandardButton DialogMaster::question(QWidget *parent, const QString &text, const QString &title, const QString &windowTitle, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton, QMessageBox::StandardButton escapeButton)
{
	return msgBox(parent,
				  QMessageBox::Question,
				  text,
				  title,
				  windowTitle.isEmpty() ? QCoreApplication::translate("DialogMaster", "Question") : windowTitle,
				  QString(),
				  NULL,
				  QString(),
				  buttons,
				  defaultButton,
				  escapeButton);
}

QMessageBox::StandardButton DialogMaster::question(QWidget *parent, const QString &text, const QString &title, const QString &windowTitle, QMessageBox::StandardButton button1, QMessageBox::StandardButton button2)
{
	return msgBox(parent,
				  QMessageBox::Question,
				  text,
				  title,
				  windowTitle.isEmpty() ? QCoreApplication::translate("DialogMaster", "Question") : windowTitle,
				  QString(),
				  NULL,
				  QString(),
				  button1 | button2,
				  button1,
				  button2);
}

QMessageBox::StandardButton DialogMaster::warning(QWidget *parent, const QString &text, const QString &title, const QString &windowTitle, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton, QMessageBox::StandardButton escapeButton)
{
	return msgBox(parent,
				  QMessageBox::Warning,
				  text,
				  title,
				  windowTitle.isEmpty() ? QCoreApplication::translate("DialogMaster", "Warning") : windowTitle,
				  QString(),
				  NULL,
				  QString(),
				  buttons,
				  defaultButton,
				  escapeButton);
}

QMessageBox::StandardButton DialogMaster::warning(QWidget *parent, const QString &text, const QString &title, const QString &windowTitle, QMessageBox::StandardButton button1, QMessageBox::StandardButton button2)
{
	return msgBox(parent,
				  QMessageBox::Warning,
				  text,
				  title,
				  windowTitle.isEmpty() ? QCoreApplication::translate("DialogMaster", "Warning") : windowTitle,
				  QString(),
				  NULL,
				  QString(),
				  button1 | button2,
				  button1,
				  button2);
}

QMessageBox::StandardButton DialogMaster::critical(QWidget *parent, const QString &text, const QString &title, const QString &windowTitle, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton, QMessageBox::StandardButton escapeButton)
{
	return msgBox(parent,
				  QMessageBox::Critical,
				  text,
				  title,
				  windowTitle.isEmpty() ? QCoreApplication::translate("DialogMaster", "Error") : windowTitle,
				  QString(),
				  NULL,
				  QString(),
				  buttons,
				  defaultButton,
				  escapeButton);
}

QMessageBox::StandardButton DialogMaster::critical(QWidget *parent, const QString &text, const QString &title, const QString &windowTitle, QMessageBox::StandardButton button1, QMessageBox::StandardButton button2)
{
	return msgBox(parent,
				  QMessageBox::Critical,
				  text,
				  title,
				  windowTitle.isEmpty() ? QCoreApplication::translate("DialogMaster", "Error") : windowTitle,
				  QString(),
				  NULL,
				  QString(),
				  button1 | button2,
				  button1,
				  button2);
}



DialogMaster::MessageBoxIcon::MessageBoxIcon(QMessageBox::Icon mbxIcon) :
	isCustom(false),
	mbxIcon(mbxIcon),
	custIcon()
{}

DialogMaster::MessageBoxIcon::MessageBoxIcon(const QPixmap &custIcon) :
	isCustom(true),
	mbxIcon(),
	custIcon(custIcon.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation))
{}

DialogMaster::MessageBoxIcon::MessageBoxIcon(const QIcon &custIcon) :
	isCustom(true),
	mbxIcon(),
	custIcon(custIcon.pixmap(64, 64))
{}

double DialogMaster::getDouble(QWidget *parent, const QString &label, double value, double min, double max, const QString &title, int decimals, bool *ok)
{
	QInputDialog dialog(parent);
	dialog.setWindowTitle(title);
	dialog.setLabelText(label);
	dialog.setInputMode(QInputDialog::DoubleInput);
	dialog.setDoubleRange(min, max);
	dialog.setDoubleDecimals(decimals);
	dialog.setDoubleValue(value);

	DialogMaster::masterDialog(&dialog, true);
	if(dialog.exec() == QDialog::Accepted) {
		if(ok)
			*ok = true;
		return dialog.doubleValue();
	} else {
		if(ok)
			*ok = false;
		return value;
	}
}

int DialogMaster::getInt(QWidget *parent, const QString &label, int value, int min, int max, const QString &title, int step, bool *ok)
{
	QInputDialog dialog(parent);
	dialog.setWindowTitle(title);
	dialog.setLabelText(label);
	dialog.setInputMode(QInputDialog::IntInput);
	dialog.setIntRange(min, max);
	dialog.setIntStep(step);
	dialog.setIntValue(value);

	DialogMaster::masterDialog(&dialog, true);
	if(dialog.exec() == QDialog::Accepted) {
		if(ok)
			*ok = true;
		return dialog.intValue();
	} else {
		if(ok)
			*ok = false;
		return value;
	}
}

QString DialogMaster::getItem(QWidget *parent, const QString &label, const QStringList &items, const QString &title, int current, bool editable, bool *ok, Qt::InputMethodHints inputMethodHints)
{
	QInputDialog dialog(parent);
	dialog.setWindowTitle(title);
	dialog.setLabelText(label);
	dialog.setInputMode(QInputDialog::TextInput);
	dialog.setComboBoxItems(items);
	dialog.setComboBoxEditable(editable);
	dialog.setTextValue(items[current]);
	dialog.setInputMethodHints(inputMethodHints);
	dialog.setOptions(QInputDialog::UseListViewForComboBoxItems);

	DialogMaster::masterDialog(&dialog);
	if(dialog.exec() == QDialog::Accepted) {
		if(ok)
			*ok = true;
		return dialog.textValue();
	} else {
		if(ok)
			*ok = false;
		return items[current];
	}
}

int DialogMaster::getItemIndex(QWidget *parent, const QString &label, const QStringList &items, const QString &title, int current, bool *ok)
{
	QInputDialog dialog(parent);
	dialog.setWindowTitle(title);
	dialog.setLabelText(label);
	dialog.setInputMode(QInputDialog::TextInput);
	dialog.setComboBoxItems(items);
	dialog.setComboBoxEditable(false);
	dialog.setTextValue(items[current]);

	DialogMaster::masterDialog(&dialog, true);
	if(dialog.exec() == QDialog::Accepted) {
		if(ok)
			*ok = true;
		return items.indexOf(dialog.textValue());
	} else {
		if(ok)
			*ok = false;
		return current;
	}
}

QString DialogMaster::getMultiLineText(QWidget *parent, const QString &label, const QString &title, const QString &text, bool *ok, Qt::InputMethodHints inputMethodHints)
{
	QInputDialog dialog(parent);
	dialog.setWindowTitle(title);
	dialog.setLabelText(label);
	dialog.setInputMode(QInputDialog::TextInput);
	dialog.setTextValue(text);
	dialog.setInputMethodHints(inputMethodHints);
	dialog.setOption(QInputDialog::UsePlainTextEditForTextInput);

	DialogMaster::masterDialog(&dialog);
	if(dialog.exec() == QDialog::Accepted) {
		if(ok)
			*ok = true;
		return dialog.textValue();
	} else {
		if(ok)
			*ok = false;
		return text;
	}
}

QString DialogMaster::getText(QWidget *parent, const QString &label, const QString &title, QLineEdit::EchoMode mode, const QString &text, bool *ok, Qt::InputMethodHints inputMethodHints)
{
	QInputDialog dialog(parent);
	dialog.setWindowTitle(title);
	dialog.setLabelText(label);
	dialog.setInputMode(QInputDialog::TextInput);
	dialog.setTextEchoMode(mode);
	dialog.setTextValue(text);
	dialog.setInputMethodHints(inputMethodHints);

	DialogMaster::masterDialog(&dialog);
	if(dialog.exec() == QDialog::Accepted) {
		if(ok)
			*ok = true;
		return dialog.textValue();
	} else {
		if(ok)
			*ok = false;
		return text;
	}
}

QProgressDialog *DialogMaster::createProgress(QWidget *parent, const QString &label, const int max, const int min, bool allowCancel, const QString &windowTitle, int minimumDuration, const QString &cancelButtonText)
{
	QProgressDialog *dialog = new QProgressDialog(parent);
	DialogMaster::masterDialog(dialog, true, Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	dialog->setWindowTitle(windowTitle.isEmpty() ?
							   (parent ? parent->windowTitle() : QString()) :
							   windowTitle);

	if(max == min && max == 0) {
		QProgressBar *bar = new QProgressBar(dialog);
		bar->setTextVisible(false);
		dialog->setBar(bar);
	}

	dialog->setLabelText(label);
	if(!allowCancel) {
		dialog->installEventFilter(new CloseFilter(dialog));
		dialog->setCancelButtonText(QString());
	} else if(!cancelButtonText.isEmpty())
		dialog->setCancelButtonText(cancelButtonText);
	dialog->setMinimumDuration(minimumDuration);
	dialog->setRange(min, max);
	dialog->setValue(min);

	return dialog;
}
