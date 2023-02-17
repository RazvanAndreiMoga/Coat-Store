#include "undoredo.h"

UndoRedoAdd::UndoRedoAdd(const Coat &coat, Repository &newRepo): addedCoat(coat), repo(newRepo){

}

void UndoRedoAdd::undo() {
    int index = this->repo.find(this->addedCoat.sizeGetter(), this->addedCoat.colourGetter(), this->addedCoat.photoGetter());
    this->repo.deleteRepo(index);
}

void UndoRedoAdd::redo() {
    this->repo.addRepo(this->addedCoat);
}

UndoRedoRemove::UndoRedoRemove(const Coat &coat, Repository &newRepo): removedCoat(coat), repo(newRepo) {

}

void UndoRedoRemove::undo() {
    this->repo.addRepo(this->removedCoat);
}

void UndoRedoRemove::redo() {
    int index = this->repo.find(this->removedCoat.sizeGetter(), this->removedCoat.colourGetter(), this->removedCoat.photoGetter());
    this->repo.deleteRepo(index);
}

UndoRedoUpdate::UndoRedoUpdate(const Coat &oldCoat, const Coat &newCoat, Repository &newRepo): oldCoat(oldCoat), newCoat(newCoat), repo(newRepo) {

}

void UndoRedoUpdate::undo() {
    int index = this->repo.find(this->oldCoat.sizeGetter(), this->oldCoat.colourGetter(), this->oldCoat.photoGetter());
    this->repo.updateRepo(index, this->oldCoat);
}

void UndoRedoUpdate::redo() {
    int index = this->repo.find(this->newCoat.sizeGetter(), this->newCoat.colourGetter(), this->newCoat.photoGetter());
    this->repo.updateRepo(index, this->newCoat);
}

//UndoRedoUser::UndoRedoUser(const Coat &boughtCoat, Repository &newRepo, UserRepository *newUserRepo): boughtCoat(boughtCoat), repo(newRepo){
//    this->userRepo = newUserRepo;
//}
//
//void UndoRedoUser::undo() {
//    this->userRepo->deleteUserRepo(boughtCoat);
//    this->repo.addRepo(boughtCoat);
//}
//
//void UndoRedoUser::redo() {
//    int index = this->repo.find(this->boughtCoat.sizeGetter(), this->boughtCoat.colourGetter(), this->boughtCoat.photoGetter());
//    this->userRepo->addUserRepo(boughtCoat);
//    this->repo.deleteRepo(index);
//}
