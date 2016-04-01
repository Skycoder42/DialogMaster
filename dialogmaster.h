#ifndef MESSAGEMASTER_H
#define MESSAGEMASTER_H

#include <QDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QCheckBox>
#include <QInputDialog>
class QProgressDialog;

namespace DialogMaster
{
	// ---------- QDialog ----------
	static const Qt::WindowFlags DefaultFlags = (Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

	void masterDialog(QDialog *dialog, bool fixedSize = false, Qt::WindowFlags additionalFlags = DialogMaster::DefaultFlags);

	// ---------- QMessageBox ----------
	struct MessageBoxIcon {
		bool isCustom;
		QMessageBox::Icon mbxIcon;
		QPixmap custIcon;

		MessageBoxIcon(QMessageBox::Icon mbxIcon);
		MessageBoxIcon(const QPixmap &custIcon);
		MessageBoxIcon(const QIcon &custIcon);
	};

	struct MessageBoxInfo {
		QWidget *parent;
		MessageBoxIcon icon;
		QString text;
		QString title;
		QString windowTitle;
		QString details;
		bool *checked;
		QString checkString;
		QMessageBox::StandardButtons buttons;
		QMessageBox::StandardButton defaultButton;
		QMessageBox::StandardButton escapeButton;
		QHash<QMessageBox::StandardButton, QString> buttonTexts;

		MessageBoxInfo();
	};

	QMessageBox::StandardButton msgBox(const MessageBoxInfo &setup);



	QMessageBox::StandardButton information(QWidget *parent,
											const QString &text,
											const QString &title = QString(),
											const QString &windowTitle = QString(),
											QMessageBox::StandardButtons buttons = QMessageBox::Ok,
											QMessageBox::StandardButton defaultButton = QMessageBox::Ok,
											QMessageBox::StandardButton escapeButton = QMessageBox::Cancel);

	QMessageBox::StandardButton information(QWidget *parent,
											const QString &text,
											const QString &title,
											const QString &windowTitle,
											QMessageBox::StandardButton button1,
											QMessageBox::StandardButton button2);

	QMessageBox::StandardButton question(QWidget *parent,
										 const QString &text,
										 const QString &title = QString(),
										 const QString &windowTitle = QString(),
										 QMessageBox::StandardButtons buttons = QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No),
										 QMessageBox::StandardButton defaultButton = QMessageBox::Yes,
										 QMessageBox::StandardButton escapeButton = QMessageBox::No);

	QMessageBox::StandardButton question(QWidget *parent,
										 const QString &text,
										 const QString &title,
										 const QString &windowTitle,
										 QMessageBox::StandardButton button1,
										 QMessageBox::StandardButton button2);

	QMessageBox::StandardButton warning(QWidget *parent,
										const QString &text,
										const QString &title = QString(),
										const QString &windowTitle = QString(),
										QMessageBox::StandardButtons buttons = QMessageBox::Ok,
										QMessageBox::StandardButton defaultButton = QMessageBox::Ok,
										QMessageBox::StandardButton escapeButton = QMessageBox::Cancel);

	QMessageBox::StandardButton warning(QWidget *parent,
										const QString &text,
										const QString &title,
										const QString &windowTitle,
										QMessageBox::StandardButton button1,
										QMessageBox::StandardButton button2);

	QMessageBox::StandardButton critical(QWidget *parent,
										 const QString &text,
										 const QString &title = QString(),
										 const QString &windowTitle = QString(),
										 QMessageBox::StandardButtons buttons = QMessageBox::Ok,
										 QMessageBox::StandardButton defaultButton = QMessageBox::Ok,
										 QMessageBox::StandardButton escapeButton = QMessageBox::Cancel);

	QMessageBox::StandardButton critical(QWidget *parent,
										 const QString &text,
										 const QString &title,
										 const QString &windowTitle,
										 QMessageBox::StandardButton button1,
										 QMessageBox::StandardButton button2);

	// ---------- QInputDialog ----------
	double getDouble(QWidget *parent,
					 const QString &label,
					 double value = 0,
					 double min = INT_MIN,
					 double max = INT_MAX,
					 const QString &title = QString(),
					 int decimals = 1,
					 bool *ok = Q_NULLPTR);

	int getInt(QWidget *parent,
			   const QString &label,
			   int value = 0,
			   int min = INT_MIN,
			   int max = INT_MAX,
			   const QString &title = QString(),
			   int step = 1,
			   bool *ok = 0);

	QString getItem(QWidget *parent,
					const QString &label,
					const QStringList &items,
					const QString &title = QString(),
					int current = 0,
					bool editable = true,
					bool *ok = Q_NULLPTR,
					Qt::InputMethodHints inputMethodHints = Qt::ImhNone);

	int getItemIndex(QWidget *parent,
					 const QString &label,
					 const QStringList &items,
					 const QString &title = QString(),
					 int current = 0,
					 bool *ok = Q_NULLPTR);

	QString getMultiLineText(QWidget *parent,
							 const QString &label,
							 const QString &title = QString(),
							 const QString &text = QString(),
							 bool *ok = Q_NULLPTR,
							 Qt::InputMethodHints inputMethodHints = Qt::ImhNone);

	QString getText(QWidget *parent,
					const QString &label,
					const QString &title,
					QLineEdit::EchoMode mode = QLineEdit::Normal,
					const QString &text = QString(),
					bool *ok = Q_NULLPTR,
					Qt::InputMethodHints inputMethodHints = Qt::ImhNone);

	// ---------- QProgressDialog ----------
	QProgressDialog *createProgress(QWidget *parent,
									const QString &label,
									const int max = 0,
									const int min = 0,
									bool allowCancel = true,
									const QString &windowTitle = QString(),
									int minimumDuration = 1000,
									const QString &cancelButtonText = QString());
}

#endif // MESSAGEMASTER_H
