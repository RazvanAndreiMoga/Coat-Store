#pragma once
#include "repository.h"
#include "userrepository.h"

class UndoRedoAction {
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual ~UndoRedoAction() = default;
};

class UndoRedoAdd: public UndoRedoAction {
private:
    Coat addedCoat;
    Repository& repo;
public:
    UndoRedoAdd(const Coat& coat, Repository& newRepo);
    void undo() override;
    void redo() override;
    ~UndoRedoAdd() override = default;
};

class UndoRedoRemove: public UndoRedoAction {
private:
    Coat removedCoat;
    Repository& repo;
public:
    UndoRedoRemove(const Coat& coat, Repository& newRepo);
    void undo() override;
    void redo() override;
    ~UndoRedoRemove() override = default;
};

class UndoRedoUpdate: public UndoRedoAction {
private:
    Coat oldCoat;
    Coat newCoat;
    Repository& repo;
public:
    UndoRedoUpdate(const Coat& oldCoat, const Coat& newCoat, Repository& newRepo);
    void undo () override;
    void redo() override;
    ~UndoRedoUpdate() override = default;
};

//class UndoRedoUser: public UndoRedoAction {
//private:
//    Coat boughtCoat;
//    Repository& repo;
//    UserRepository* userRepo;
//public:
//    UndoRedoUser(const Coat& boughtCoat, Repository& newRepo, UserRepository *newUserRepo);
//    void undo() override;
//    void redo() override;
//    ~UndoRedoUser() override = default;
//};

