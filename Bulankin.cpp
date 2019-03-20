#include "authorizationdialog.h"

AuthorizationDialog::AuthorizationDialog(QWidget *parent) : QDialog(parent) {
	codec = QTextCodec::codecForLocale();

	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setModal(true);
	connect(ui.authorizeButton, SIGNAL(clicked()), this, SLOT(authorize()));
}

AuthorizationDialog::~AuthorizationDialog() {

}

void AuthorizationDialog::authorize() {
	int s = 0;
	QString login = ui.loginLineEdit->text();
	QString password = ui.passwordLineEdit->text();
	if (password.length() < MIN_PASSWORD_LENGTH) {
		QMessageBox::critical(
			this,
			codec->toUnicode("������ �����������"),
			codec->toUnicode("������ ������ ���� ������ �� ����� 6 ��������!")
			);
		return;
	}
	
	QSqlQuery query = DataBaseProvider::getQuery();
    query.prepare("SELECT id, password FROM user WHERE login = ?");
	query.addBindValue(login);
	bool success = DataBaseProvider::execQuery(query);

	int userId = 0;
	if (success) {
		if (query.size() != 0) {
			query.next();
			QString passwordHash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5));
			if (query.value(1).toString().compare(passwordHash) == 0) {
				userId = query.value(0).toInt();
			}
			else {
				QMessageBox::critical(
					this,
					codec->toUnicode("������ �����������"),
					codec->toUnicode("�������� ������!")
					);
				return;
			}
		}
		else {
			QMessageBox::critical(
				this,
				codec->toUnicode("������ �����������"),
				codec->toUnicode("�������� �����!")
				);
			return;
		}
	}

	int currentUser = userId;
	bool isAdmin = true;
	if (currentUser != 1) {
		QSqlQuery queryIdSelect = DataBaseProvider::getQuery();
		queryIdSelect.prepare("SELECT worker.id FROM user, worker WHERE worker.idUser = ?");
		queryIdSelect.addBindValue(userId);
		DataBaseProvider::execQuery(queryIdSelect);
		queryIdSelect.next();
		currentUser = queryIdSelect.value(0).toInt();
		isAdmin = false;
	}
	int gens = 0;
	emit showMainWindow(currentUser, isAdmin);
}
