#include "createproductiontypedialog.h"

CreateProductionTypeDialog::CreateProductionTypeDialog(QWidget *parent) : QDialog(parent) {
	codec = QTextCodec::codecForLocale();
	ui.setupUi(this);
	setModal(true);

	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(cancelCreate()));
	connect(ui.createProductionTypeButton, SIGNAL(clicked()), this, SLOT(createProductionType()));
}

CreateProductionTypeDialog::~CreateProductionTypeDialog() {

}

void CreateProductionTypeDialog::createProductionType() {
	if (ui.nameLineEdit->text().isEmpty()) {
		QMessageBox::warning(
			this, 
			codec->toUnicode("������ ��������"),
			codec->toUnicode("������������ ������ ��������!")
			);
		return;
	}
	QString production = ui.nameLineEdit->text();
	int cost = ui.costSpinBox->value();

	//������ � ��
	QSqlQuery query = DataBaseProvider::getQuery();
    query.prepare("INSERT INTO type_product (cost, name) VALUES (?, ?)");
    query.addBindValue(cost);
    query.addBindValue(production);
	bool success = DataBaseProvider::execQuery(query);
	int typeId = query.lastInsertId().toInt();

	emit productionTypeCreated(typeId, production, cost);	
}

void CreateProductionTypeDialog::cancelCreate() {
	reject();
}

// First comment
// Third comment
