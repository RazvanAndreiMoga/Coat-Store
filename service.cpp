#include "service.h"
#include <iterator>
#include <algorithm>

Service::Service(Repository &repo): repository(repo) {
    
}

vector<Coat> Service::getAllService() {
    return this->repository.getAllRepo();
}

int Service::getNrElemsService() {
    return this->repository.getNrElems();
}

int Service::getCapService() {
    return this->repository.getCap();
}

int Service::addService(string size, string colour, int price, int quantity, string photograph) {
    int index;
    int length = this->repository.getNrElems();
    for (index = 0; index < length; index++) {
        string other_size = this->getAllService()[index].sizeGetter();
        string other_colour = this->getAllService()[index].colourGetter();
        string other_photograph = this->getAllService()[index].photoGetter();
        if (other_size == size && other_colour == colour && other_photograph == photograph)
            return 1;
    }
    this->repository.addRepo(Coat(size, colour, price, quantity, photograph));
    Coat coat = Coat(size, colour, price, quantity, photograph);
    std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoAdd>(coat, this->repository);
    this->undoAdmin.push_back(action);
    return 0;
}

int Service::deleteService(int index) {
    index -= 1;
    if (index == -1)
        return 1;
    else {
        Coat coat = this->repository.getAllRepo()[index];
        this->repository.deleteRepo(index);
        std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoRemove>(coat, this->repository);
        this->undoAdmin.push_back(action);
        return 0;
    }
}

int Service::updateService(int index, string new_size, string new_colour, int new_price, int new_quantity, string new_photo) {
    index -= 1;
    if (index == -1)
        return 1;

    Coat old_coat = this->repository.getAllRepo()[index];
    Coat new_Coat = Coat(new_size, new_colour, new_price, new_quantity, new_photo);
    this->repository.updateRepo(index, new_Coat);
    std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoUpdate>(old_coat, new_Coat, this->repository);
    this->undoAdmin.push_back(action);
    return 0;
}

void Service::undoLastAction() {
    if (this->undoAdmin.empty()) {
        std::string error;
        error += std::string("No more undoes left!");
        if (!error.empty())
            throw RepositoryException(error);
    }
    this->undoAdmin.back()->undo();
    this->redoAdmin.push_back(this->undoAdmin.back());
    this->undoAdmin.pop_back();
}

void Service::redoLastAction() {
    if (this->redoAdmin.empty()) {
        std::string error;
        error += std::string("No more redoes left!");
        if (!error.empty())
            throw RepositoryException(error);
    }
    this->redoAdmin.back()->redo();
    this->undoAdmin.push_back(this->redoAdmin.back());
    this->redoAdmin.pop_back();
}

void Service::clearUndoRedo() {
    this->undoAdmin.clear();
    this->redoAdmin.clear();
}

Service::~Service() = default;