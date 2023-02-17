#pragma once
#include <QWidget>
#include "service.h"
#include <QLabel>
#include <QPushButton>
#include "userservice.h"
#include <QListWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QRadioButton>
#include "validator.h"
#include <QTableView>
#include <QShortcut>
#include <QHeaderView>

//class CoatListModel: public QAbstractListModel {
//private:
//    Repository& repository;
//public:
//    explicit CoatListModel(Repository& repo): repository{ repo } {};
//
//    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
//    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
//};

class CoatTableModel : public QAbstractTableModel {
private:
    UserRepository* repository;
public:
    explicit CoatTableModel(UserRepository* newRepository);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void update();
};

class GUI: public QWidget {
private:
    Service& service;
    UserService& userService;
    CoatValidator& validator;
    Repository& repository;
    void initGUI();
    QLabel* titleWidget;
    QPushButton* adminButton;
    QPushButton* userButton;
    void showAdmin();
    void paintEvent(QPaintEvent* event);
    void showUser();
    void connectSignalsAndSlots();
public:
    explicit GUI(Service& serv, UserService& userserv, CoatValidator& validator1, Repository& repository);
    ~GUI() override;
};

class AdminGUI: public QWidget {
private:
    Service& service;
    CoatValidator& validator;
    Repository& repository;
    void initAdminGUI();
    //void paintEvent(QPaintEvent* event);
    QLabel* titleWidget;
    QListWidget *coatsListWidget;
    QLineEdit *sizeLineEdit, *colourLineEdit, *priceLineEdit, *quantityLineEdit, *linkLineEdit;
    QPushButton* addButton, *deleteButton, *updateButton, *chartButton;
    QPushButton* undoButton, * redoButton;
    QShortcut* shortcutUndo, * shortcutRedo;
    //CoatListModel* listModel;

    void populateList();
    void connectSignalsAndSlots();
    int getSelectedIndex() const;
    void addCoat();
    void deleteCoat();
    void updateCoat();
    void displayChart();
    void undoGUI();
    void redoGUI();

    QWidget* chartWindow;
public:
    explicit AdminGUI(QWidget* parent, Service& serv, CoatValidator& validator1, Repository& repo);
    ~AdminGUI() override;
};

class UserGUI: public QWidget {
private:
    Service& service;
    UserService& userService;
    CoatValidator& validator;
    void initUserGUI();
    QLabel* titleWidget;
    QListWidget* coatsListWidget, *basketListWidget;
    QLineEdit* sizeLineEdit, * colourLineEdit, * priceLineEdit, * quantityLineEdit, * linkLineEdit, * sizeFilterLineEdit;
    QPushButton* addButton, *filterButton, *openListButton;
    QRadioButton* csvButton, *htmlButton;
    QTableView* adoptionListTable;
    CoatTableModel* adoptionListTableModel;
    QGridLayout* listAndTableLayout;
    bool repoTypeSelected;
    bool filtered;
    void createTable();
    void populateCoatList();
    void populateBasketList();
    void connectSignalsAndSlots();
    int getSelectedIndex() const;
    void addCoat();
    void filterCoats();
    
public:
    explicit UserGUI(QWidget* parent, Service& serv, UserService& userserv, CoatValidator& validator1);
    ~UserGUI() override;
};
