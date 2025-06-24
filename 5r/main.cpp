#include <memory>
#include <iostream>
#include <print>

import JsonUserRepository;
import JsonAuthService;
import User;

int main() {
    auto userRepo = std::make_shared<JsonUserRepository>("users.json");
    auto authService = std::make_shared<JsonAuthService>(userRepo, "auth.json");

    User user1(1, "Alice", "alice", "123", "alice@example.com", "Kaliningrad");
    User user2(2, "Bob", "bob", "admin", std::nullopt, "World");
    User user3(3, "Charlie", "qwerty", "charpass", "charlie@test.com", std::nullopt);

    userRepo->add(user1);
    userRepo->add(user2);
    userRepo->add(user3);

    std::println("Пользователи: ");
    auto allUsers = userRepo->getAll();
    std::sort(allUsers.begin(), allUsers.end()); 
    for (const auto& user : allUsers) {
        std::println( "{}", user.toString() );
    }

    std::println("\nАлиса входит");
    authService->signIn(user1);
    if (authService->isAuthorized()) {
        std::println( "Проверка текущего пользователя: {}", authService->getCurrentUser()->toString() );
    }

    std::cout << "\nЛогинится Боб" << std::endl;
    authService->signOut();
    authService->signIn(user2);
    if (authService->isAuthorized()) {
        std::println( "Проверка текущего пользователя: {}", authService->getCurrentUser()->toString() );
    }

    auto bob = userRepo->getByLogin("bob");
    if (bob) {
        bob->setName("Robert");
        bob->setEmail("robert@example.org");
        userRepo->update(*bob);
        std::println("\nБоб решил изменить свою личность:");
        std::println( "{}", userRepo->getByLogin("bob")->toString() );
    }

    std::cout << "Проверка автоматического входа при новой сессии" << std::endl;
    auto newAuthService = std::make_shared<JsonAuthService>(userRepo, "auth.json");
    if (newAuthService->isAuthorized()) {
        std::println( "Auto-authorized user: {}", newAuthService->getCurrentUser()->toString() );
    } 

    return 0;
}
