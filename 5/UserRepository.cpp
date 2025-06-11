export module UserRepository;

export import User;
import DataRepository;

export using UserRepository = DataRepository<User>;
