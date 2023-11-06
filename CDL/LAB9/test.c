main() {
    int choice;
    int a,b,soln;
    a=5;
    b=3;
    choice=1;
    switch (choice) {
        case 1:
            soln=a+b;
            break;
        case 2:
            soln=a;
            break;
        case 3:
            soln=b;
            break;
        default:
            soln=0;
    }

    return 0;
}