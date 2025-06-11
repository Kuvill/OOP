#include <memory>
#include <iostream>
#include <fstream>

import JsonUserRepository;
import JsonAuthService;
import User;

int main() {
    auto userRepo = std::make_shared<JsonUserRepository>("users.json");
    auto authService = std::make_shared<JsonAuthService>(userRepo, "auth.json");

    User user1(1, "Alice", "alice", "pass123", "alice@example.com", "123 Main St");
    User user2(2, "Bob", "bob", "bobpass", std::nullopt, "456 Oak Ave");
    User user3(3, "Charlie", "charlie", "charpass", "charlie@test.com", std::nullopt);

    userRepo->add(user1);
    userRepo->add(user2);
    userRepo->add(user3);

    std::cout << "All users:" << std::endl;
    auto allUsers = userRepo->getAll();
    std::sort(allUsers.begin(), allUsers.end()); 
    for (const auto& user : allUsers) {
        std::cout << user.toString() << std::endl;
    }

    std::cout << "\nSigning in Alice..." << std::endl;
    authService->signIn(user1);
    if (authService->isAuthorized()) {
        std::cout << "Current user: " << authService->getCurrentUser()->toString() << std::endl;
    }

    std::cout << "\nSigning out and signing in Bob..." << std::endl;
    authService->signOut();
    authService->signIn(user2);
    if (authService->isAuthorized()) {
        std::cout << "Current user: " << authService->getCurrentUser()->toString() << std::endl;
    }

    auto bob = userRepo->getByLogin("bob");
    if (bob) {
        bob->setName("Robert");
        bob->setEmail("robert@example.org");
        userRepo->update(*bob);
        std::cout << "\nUpdated Bob:" << std::endl;
        std::cout << userRepo->getByLogin("bob")->toString() << std::endl;
    }

    std::cout << "\nCreating new auth service to demonstrate auto auth..." << std::endl;
    auto newAuthService = std::make_shared<JsonAuthService>(userRepo, "auth.json");
    if (newAuthService->isAuthorized()) {
        std::cout << "Auto-authorized user: " << newAuthService->getCurrentUser()->toString() << std::endl;
    } else {
        std::cout << "No auto-auth performed" << std::endl;
    }

    newAuthService->signOut();
    std::cout << "\nAfter sign out, is authorized: " << std::boolalpha << newAuthService->isAuthorized() << std::endl;

    return 0;
}
