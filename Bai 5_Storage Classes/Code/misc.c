int main() {
    const char *username = "user1"; // Giả sử người dùng nhập
    const char *password = "pass1"; // Giả sử người dùng nhập

    extract_users_file("kernel.zip", "users.txt");

    if (authenticate_user(username, password)) {
        update_access_status(username, 1);
        compile_and_run_kernel();
        reset_access_status();
    } else {
        printf("Xác thực thất bại.\n");
    }

    return 0;
}