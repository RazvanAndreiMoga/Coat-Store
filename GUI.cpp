#include <QVBoxLayout>
#include <QFormLayout>
#include <QErrorMessage>
#include <QMessageBox>
#include <QLinearGradient>
#include "QtCharts/qchartview.h"
#include "QtCharts/qbarseries.h"
#include "QtCharts/qbarset.h"
#include "QtCharts/qbarcategoryaxis.h"
#include "QtCharts/qvalueaxis.h"
#include "GUI.h"
#include "picturedelegate.h"

CoatTableModel::CoatTableModel(UserRepository* newRepository) {
    this->repository = newRepository;
}

int CoatTableModel::rowCount(const QModelIndex& parent) const {
    return this->repository->getNrElems();
}

int CoatTableModel::columnCount(const QModelIndex& parent) const {
    return 6;
}

QVariant CoatTableModel::data(const QModelIndex& index, int role) const {
    int row = index.row();
    Coat currentCoat = this->repository->getAllUserRepo()[row];
    int column = index.column();
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (column) {
        case 0:
            return QString::fromStdString(currentCoat.sizeGetter());
        case 1:
            return QString::fromStdString(currentCoat.colourGetter());
        case 2:
            return QString::fromStdString(std::to_string(currentCoat.priceGetter()));
        case 3:
            return QString::fromStdString(std::to_string(currentCoat.quantityGetter()));
        case 4:
            return QString::fromStdString(currentCoat.photoGetter());
        case 5:
            return QString::fromStdString(currentCoat.photoGetter());
        default:
            break;
        }
    }
    return QVariant();
}

QVariant CoatTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("Size");
            case 1:
                return QString("Colour");
            case 2:
                return QString("Price");
            case 3:
                return QString("Quantity");
            case 4:
                return QString("Photo link");
            case 5:
                return QString("Coat photo");
            default:
                break;
            }
        }
    }
    return QVariant();
}

void CoatTableModel::update() {
    QModelIndex topLeft = this->index(1, 1);
    QModelIndex bottomRight = this->index(this->rowCount(), this->columnCount());
    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);
}

GUI::GUI(Service& serv, UserService& userserv, CoatValidator& validator1,Repository& repository): service{serv}, userService{userserv}, validator{validator1}, repository{repository}{
    this->titleWidget = new QLabel(this);
    this->adminButton = new QPushButton(this);
    this->userButton = new QPushButton(this);
    this->initGUI();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    auto* layout = new QVBoxLayout(this);
    QFont titleFont = this->titleWidget->font();
    this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>Welcome to the Proper Trench Coats App! <br> Select your mode!</font></p>");
    titleFont.setItalic(true);
    titleFont.setPointSize(10);
    titleFont.setStyleHint(QFont::System);
    titleFont.setLegacyWeight(63);
    this->titleWidget->setFont(titleFont);
    layout->addWidget(this->titleWidget);
    this->adminButton->setText("Admin mode");
    layout->addWidget(this->adminButton);
    this->userButton->setText("User mode");
    layout->addWidget(this->userButton);
    this->setLayout(layout);
    this->setStyleSheet("background-color:#D9DBF1");
}

GUI::~GUI() = default;

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::showAdmin);
    QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::showUser);
}

void GUI::showAdmin() {
    this->service.clearUndoRedo();
    auto* admin = new AdminGUI(this, this->service, this->validator, this->repository);
    admin->show();
}
//
AdminGUI::AdminGUI(QWidget* parent, Service &serv, CoatValidator& validator1, Repository& repo): service{serv}, validator{validator1}, repository{repo}{
    this->titleWidget = new QLabel(this);
    this->coatsListWidget = new QListWidget{};
    this->sizeLineEdit = new QLineEdit{};
    this->colourLineEdit = new QLineEdit{};
    this->priceLineEdit = new QLineEdit{};
    this->quantityLineEdit = new QLineEdit{};
    this->linkLineEdit = new QLineEdit{};
    this->addButton = new QPushButton("Add");
    this->deleteButton = new QPushButton("Delete");
    this->updateButton = new QPushButton("Update");
    this->chartButton = new QPushButton("Display chart");
    this->undoButton = new QPushButton("Undo");
    this->redoButton = new QPushButton("Redo");
    this->shortcutUndo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    this->shortcutRedo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
    setParent(parent);
    setWindowFlag(Qt::Window);
    this->initAdminGUI();
    this->populateList();
    this->connectSignalsAndSlots();

    //this->listModel = new CoatListModel{this->repository};
//    
}

void AdminGUI::initAdminGUI() {
    auto* layout = new QVBoxLayout(this);
    QFont titleFont = this->titleWidget->font();
    this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>ADMIN MODE</font></p>");
    titleFont.setItalic(true);
    titleFont.setPointSize(10);
    titleFont.setStyleHint(QFont::System);
    titleFont.setLegacyWeight(63);
    this->titleWidget->setFont(titleFont);
    layout->addWidget(this->titleWidget);

    layout->addWidget(this->coatsListWidget);

    auto * coatDetailsLayout = new QFormLayout{};
    coatDetailsLayout->addRow("Size", this->sizeLineEdit);
    coatDetailsLayout->addRow("Colour", this->colourLineEdit);
    coatDetailsLayout->addRow("Price", this->priceLineEdit);
    coatDetailsLayout->addRow("Quantity", this->quantityLineEdit);
    coatDetailsLayout->addRow("Link", this->linkLineEdit);
    layout->addLayout(coatDetailsLayout);

    auto* buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(this->addButton, 0, 0);
    buttonsLayout->addWidget(this->deleteButton, 0, 1);
    buttonsLayout->addWidget(this->updateButton, 1, 0);
    buttonsLayout->addWidget(this->chartButton, 1, 1);
    buttonsLayout->addWidget(this->undoButton, 2, 0);
    buttonsLayout->addWidget(this->redoButton, 2, 1);
    layout->addLayout(buttonsLayout);
}

void GUI::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    QLinearGradient linearGradient(QPointF(100, 100), QPointF(200, 200));
    linearGradient.setColorAt(0, Qt::black);
    linearGradient.setColorAt(1, Qt::white);
    QRect linearRect(0, 0, width(), height());
    painter.fillRect(linearRect, linearGradient);
}

//
void AdminGUI::populateList() {
    this->coatsListWidget->clear();
    std::vector<Coat> allCoats = this->service.getAllService();
    for (Coat& coat: allCoats)
        this->coatsListWidget->addItem(QString::fromStdString(coat.toString()));
}
//
void AdminGUI::connectSignalsAndSlots() {
    QObject::connect(this->coatsListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex < 0)
            return ;
        Coat coat = this->service.getAllService()[selectedIndex];
        this->sizeLineEdit->setText(QString::fromStdString(coat.sizeGetter()));
        this->colourLineEdit->setText(QString::fromStdString(coat.colourGetter()));
        this->priceLineEdit->setText(QString::fromStdString(std::to_string(coat.priceGetter())));
        this->quantityLineEdit->setText(QString::fromStdString(std::to_string(coat.quantityGetter())));
        this->linkLineEdit->setText(QString::fromStdString(coat.photoGetter()));
    });

    QObject::connect(this->shortcutUndo, &QShortcut::activated, this, &AdminGUI::undoGUI);
    QObject::connect(this->shortcutRedo, &QShortcut::activated, this, &AdminGUI::redoGUI);

    QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addCoat);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::deleteCoat);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::updateCoat);
    QObject::connect(this->chartButton, &QPushButton::clicked, this, &AdminGUI::displayChart);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &AdminGUI::undoGUI);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &AdminGUI::redoGUI);
}
//
void AdminGUI::addCoat() {
    std::string size = this->sizeLineEdit->text().toStdString();
    std::string colour = this->colourLineEdit->text().toStdString();
    std::string price_s = this->priceLineEdit->text().toStdString();
    std::string quantity_s = this->quantityLineEdit->text().toStdString();
    std::string link = this->linkLineEdit->text().toStdString();
    int price, quantity;
    try {
        this->validator.validateSize(size);
        this->validator.validateColour(colour);
        this->validator.validatePriceString(price_s);
        price = stoi(price_s);
        this->validator.validatePrice(price);
        this->validator.validateQuantityString(quantity_s);
        quantity = stoi(quantity_s);
        this->validator.validateQuantity(quantity);
        this->validator.validatePhotoLink(link);
        this->service.addService(size, colour, price, quantity, link);
        this->populateList();
    } catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    } catch (RepositoryException& re) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(re.what());
        error->setWindowTitle("Error at adding coat!");
        error->exec();
    }
}
//
void AdminGUI::deleteCoat() {
    int index = this->getSelectedIndex();
    try {
        if (index < 0) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText("No coat selected!");
            error->setWindowTitle("Selection error!");
            error->exec();
        }
        else {
            this->service.deleteService(index);
            this->populateList();
        }
    } catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    } catch (RepositoryException& re) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(re.what());
        error->setWindowTitle("Error at deleting coat!");
        error->exec();
    }
}
//
void AdminGUI::updateCoat() {
    int index = this->getSelectedIndex() + 1;
    try {
        if (index < 0) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText("No coat selected!");
            error->setWindowTitle("Selection error!");
            error->exec();
        } else {
            std::string new_size = this->sizeLineEdit->text().toStdString();
            std::string new_colour = this->colourLineEdit->text().toStdString();
            std::string price_s = this->priceLineEdit->text().toStdString();
            int new_price, new_quantity;
            std::string quantity_s = this->quantityLineEdit->text().toStdString();
            int quantity;
            std::string new_link = this->linkLineEdit->text().toStdString();
            this->validator.validateSize(new_size);
            this->validator.validateColour(new_colour);
            this->validator.validatePriceString(price_s);
            new_price = stoi(price_s);
            this->validator.validatePrice(new_price);
            this->validator.validateQuantityString(quantity_s);
            new_quantity = stoi(quantity_s);
            this->validator.validateQuantity(new_quantity);            
            this->validator.validatePhotoLink(new_link);
            this->service.updateService(index, new_size, new_colour, new_price, new_quantity, new_link);
            this->populateList();
        }
    } catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    } catch (RepositoryException& re) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(re.what());
        error->setWindowTitle("Error at updating coat!");
        error->exec();
    }
}
//
void AdminGUI::displayChart() {
    /*this->chartWindow = new QWidget{};
    auto* chartLayout = new QVBoxLayout(this->chartWindow);
    this->chartWindow->setStyleSheet("background-color:#D9DBF1");
    std::vector<std::string> sizes = this->service.getAllSizes();
    auto* chart = new QChart();
    auto *axis_x = new QBarCategoryAxis();
    axis_x->setTitleText("Sizes");

    QStringList categories;
    for (int i = 1; i <= sizes.size(); i++) {
        categories << QString::fromStdString(std::to_string(i));
    }

    axis_x->append(categories);
    chart->addAxis(axis_x, Qt::AlignBottom);

    auto* axis_y = new QValueAxis();
    chart->addAxis(axis_y, Qt::AlignLeft);
    axis_y->setRange(0, 8);
    axis_y->setTitleText("Number of coats");

    for (std::string& size: sizes) {
        auto *series = new QBarSeries();
        auto* set = new QBarSet(QString::fromStdString(size));
        int number_of_coats = this->service.numberOfCoatsPerSize(size);
        *set << number_of_coats;
        series->append(set);
        chart->addSeries(series);
        series->attachAxis(axis_y);
    }

    chart->setTitle("Number of coats per size");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignLeft);
    chart->legend()->setBackgroundVisible(true);
    chart->legend()->setBorderColor(QColor::fromRgb(171, 147, 225));
    chart->legend()->setFont(QFont("Cambria Math", 7));
    auto* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartLayout->addWidget(chartView);
    this->chartWindow->resize(840, 720);
    this->chartWindow->show();*/
}
//
int AdminGUI::getSelectedIndex() const {
    QModelIndexList selectedIndexes = this->coatsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty()) {
        this->sizeLineEdit->clear();
        this->colourLineEdit->clear();
        this->priceLineEdit->clear();
        this->quantityLineEdit->clear();
        this->linkLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void AdminGUI::undoGUI() {
    try {
        this->service.undoLastAction();
        this->populateList();
    }
    catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
    }
}

void AdminGUI::redoGUI() {
    try {
        this->service.redoLastAction();
        this->populateList();
    }
    catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
    }
}

//
AdminGUI::~AdminGUI() = default;
//
void GUI::showUser() {
    auto* user = new UserGUI(this, this->service, this->userService, this->validator);
    user->show();
}
//
//
UserGUI::UserGUI(QWidget* parent, Service& serv, UserService &userserv, CoatValidator& validator1): service{serv}, userService{userserv}, validator{validator1} {
    this->titleWidget = new QLabel(this);
    this->coatsListWidget = new QListWidget{};
    this->basketListWidget = new QListWidget{};
    this->sizeLineEdit = new QLineEdit{};
    this->colourLineEdit = new QLineEdit{};
    this->priceLineEdit = new QLineEdit{};
    this->quantityLineEdit = new QLineEdit{};
    this->linkLineEdit = new QLineEdit{};
    this->sizeFilterLineEdit = new QLineEdit{};
    this->addButton = new QPushButton("Add to the shopping basket");
    this->filterButton = new QPushButton("Filter");
    this->openListButton = new QPushButton("Open file");
    this->csvButton = new QRadioButton("CSV");
    this->htmlButton = new QRadioButton("HTML");
    this->repoTypeSelected = false;
    this->filtered = false;
    setParent(parent);
    setWindowFlag(Qt::Window);
    this->initUserGUI();
    this->populateCoatList();
    this->connectSignalsAndSlots();
}
//
void UserGUI::initUserGUI() {
    auto* layout = new QVBoxLayout(this);
    QFont titleFont = this->titleWidget->font();
    this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>USER MODE <br> Select the type of file you want for saving your shopping basket!</font></p>");
    titleFont.setItalic(true);
    titleFont.setPointSize(10);
    titleFont.setStyleHint(QFont::System);
    titleFont.setLegacyWeight(63);
    this->titleWidget->setFont(titleFont);
    layout->addWidget(this->titleWidget);

    auto* radioButtonsLayout = new QGridLayout(this);
    radioButtonsLayout->addWidget(this->csvButton, 0, 0);
    radioButtonsLayout->addWidget(this->htmlButton, 1, 0);
    radioButtonsLayout->addWidget(this->openListButton, 0, 1);
    layout->addLayout(radioButtonsLayout);

    this->listAndTableLayout = new QGridLayout(this);
    this->listAndTableLayout->addWidget(this->coatsListWidget, 0, 0);
    layout->addLayout(this->listAndTableLayout);

    auto * coatDetailsLayout = new QFormLayout{};
    coatDetailsLayout->addRow("Size", this->sizeLineEdit);
    coatDetailsLayout->addRow("Colour", this->colourLineEdit);
    coatDetailsLayout->addRow("Price", this->priceLineEdit);
    coatDetailsLayout->addRow("Quantity", this->quantityLineEdit);
    coatDetailsLayout->addRow("Link", this->linkLineEdit);
    coatDetailsLayout->addRow(this->addButton);
    layout->addLayout(coatDetailsLayout);


    auto *filterTitle = new QLabel("<p style='text-align:center'><font color=#4D2D52><br>Filter the available coats by size</font></p>");
    QFont filterFont = filterTitle->font();
    filterFont.setPointSize(10);
    filterFont.setStyleHint(QFont::System);
    filterFont.setLegacyWeight(63);
    filterTitle->setFont(filterFont);
    layout->addWidget(filterTitle);

    auto *  filterDetailsLayout = new QFormLayout{};
    filterDetailsLayout->addRow("Size", this->sizeFilterLineEdit);
    filterDetailsLayout->addRow(this->filterButton);
    layout->addLayout(filterDetailsLayout);
}
//
void UserGUI::createTable() {
    this->adoptionListTableModel = new CoatTableModel{ this->userService.getUserRepo() };
    this->adoptionListTable = new QTableView{};
    this->adoptionListTable->setModel(this->adoptionListTableModel);
    this->adoptionListTable->setItemDelegate(new PictureDelegate{});
    this->listAndTableLayout->addWidget(this->adoptionListTable, 0, 1);
    this->adoptionListTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->resize(900, 500);
}


void UserGUI::populateCoatList() {
    this->coatsListWidget->clear();
    std::vector<Coat> allCoats = this->service.getAllService();
    for (Coat& coat: allCoats)
        this->coatsListWidget->addItem(QString::fromStdString(coat.toString()));
}
//
void UserGUI::connectSignalsAndSlots() {
//
    /*QObject::connect(this->coatsListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex < 0)
            return;
        Coat coat = this->service.getAllService()[selectedIndex];
        this->sizeLineEdit->setText(QString::fromStdString(coat.sizeGetter()));
        this->colourLineEdit->setText(QString::fromStdString(coat.colourGetter()));
        this->priceLineEdit->setText(QString::fromStdString(std::to_string(coat.priceGetter())));
        this->quantityLineEdit->setText(QString::fromStdString(std::to_string(coat.quantityGetter())));
        this->linkLineEdit->setText(QString::fromStdString(coat.photoGetter()));
        std::string link = std::string("start ").append(coat.photoGetter());
        system(link.c_str());
        });*/

    QObject::connect(this->coatsListWidget, &QListWidget::itemClicked, [this]() {   
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex < 0)
            return;
        Coat coat = this->service.getAllService()[selectedIndex];
        this->sizeLineEdit->setText(QString::fromStdString(coat.sizeGetter()));
        this->colourLineEdit->setText(QString::fromStdString(coat.colourGetter()));
        this->priceLineEdit->setText(QString::fromStdString(std::to_string(coat.priceGetter())));
        this->quantityLineEdit->setText(QString::fromStdString(std::to_string(coat.quantityGetter())));
        this->linkLineEdit->setText(QString::fromStdString(coat.photoGetter()));
        std::string link = std::string("start ").append(coat.photoGetter());
        system(link.c_str());
    });

    QObject::connect(this->csvButton, &QRadioButton::clicked, [this]() {
        this->userService.repositoryType("csv");
        this->repoTypeSelected = true;
        this->createTable();
    });

    QObject::connect(this->htmlButton, &QRadioButton::clicked, [this]() {
        this->userService.repositoryType("html");
        this->repoTypeSelected = true;
        this->createTable();
    });

    QObject::connect(this->openListButton, &QPushButton::clicked, [this]() {
        if (!this->repoTypeSelected) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Warning);
            error->setText("Please select the type of file you want!");
            error->setWindowTitle("File type warning!");
            error->exec();
        } else {
            std::string link = std::string("start ").append(this->userService.getFileService());
            system(link.c_str());
        }
    });

    QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addCoat);
    QObject::connect(this->filterButton, &QPushButton::clicked, this, &UserGUI::filterCoats);
}
//
int UserGUI::getSelectedIndex() const {
    QModelIndexList selectedIndexes = this->coatsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty()) {
        this->sizeLineEdit->clear();
        this->colourLineEdit->clear();
        this->priceLineEdit->clear();
        this->quantityLineEdit->clear();
        this->linkLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}
//
void UserGUI::populateBasketList() {


    this->adoptionListTableModel->update();
    this->adoptionListTable->resizeRowsToContents();
    this->adoptionListTable->resizeColumnsToContents();

    //this->basketListWidget->clear();
    //std::vector<Coat> allCoats = this->userService.getAllUserService();
    //for (Coat& coat: allCoats)
    //    this->basketListWidget->addItem(QString::fromStdString(coat.toString()));
}

void UserGUI::addCoat() {
    if (!this->repoTypeSelected) {
        auto *error = new QMessageBox();
        error->setIcon(QMessageBox::Warning);
        error->setText("Please select the type of file you want!");
        error->setWindowTitle("File type warning!");
        error->exec();
    } else {
        std::string size = this->sizeLineEdit->text().toStdString();
        std::string colour = this->colourLineEdit->text().toStdString();
        std::string price_s = this->priceLineEdit->text().toStdString();
        std::string quantity_s = this->quantityLineEdit->text().toStdString();
        std::string link = this->linkLineEdit->text().toStdString();
        int price, quantity;
        try {
            this->validator.validateSize(size);
            this->validator.validateColour(colour);
            this->validator.validatePriceString(price_s);            
            price = stoi(price_s);
            this->validator.validatePrice(price);
            this->validator.validateQuantityString(quantity_s);
            quantity = stoi(quantity_s);
            this->validator.validateQuantity(quantity);
            this->validator.validatePhotoLink(link);
            Coat coat = Coat(size, colour, price, quantity, link);
            this->userService.addUserService(coat);
            if (!this->filtered)
                this->populateCoatList();
            else
                this->basketListWidget->addItem(this->coatsListWidget->takeItem(this->getSelectedIndex()));
            this->populateBasketList();
        } catch (ValidationException& exc) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText(exc.what());
            error->setWindowTitle("Invalid input!");
            error->exec();
        } catch (RepositoryException& re) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText(re.what());
            error->setWindowTitle("Error at adding coat!");
            error->exec();
        }
    }
}

void UserGUI::filterCoats(){
    try {
        std::string size_filter = this->sizeFilterLineEdit->text().toStdString();
        if (size_filter.empty()) {
            this->filtered = false;
            this->populateCoatList();
        } else {
            this->validator.validateString(size_filter);
            std::vector<Coat> validCoats;
            this->userService.getFiltered(validCoats, size_filter);
            if (validCoats.empty()) {
                std::string error;
                error += std::string("The list of valid coats is empty!");
                if(!error.empty())
                    throw UserException(error);
            } else {
                this->filtered = true;
                this->coatsListWidget->clear();
                for (Coat& coat: validCoats)
                    this->coatsListWidget->addItem(QString::fromStdString(coat.toString()));
            }
        }
    } catch (ValidationException& ve) {
        auto *error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(ve.what());
        error->setWindowTitle("Validation error!");
        error->exec();
    } catch (UserException& ue) {
        auto *error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(ue.what());
        error->setWindowTitle("Filter error!");
        error->exec();
    }
}
//
UserGUI::~UserGUI() = default;
//
//int CoatListModel::rowCount(const QModelIndex &parent) const {
//    return this->repository.getAllRepo().size();
//}
//
//QVariant CoatListModel::data(const QModelIndex &index, int role) const {
//    int row = index.row();
//    Coat currentCoat = this->repository.getAllRepo()[row];
//    if(role == Qt::DisplayRole)
//    {
//        return QString::fromStdString(currentCoat.toString());
//    }
//    return QVariant();
//}