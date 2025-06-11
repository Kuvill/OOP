module;

export module IAuthService;

export import User;

export struct IAuthService {
    virtual void sign_in( const User& usr ) = 0;

    virtual void sign_out() = 0;

    virtual bool is_authorized() = 0;

    virtual User current_user() = 0;
};
