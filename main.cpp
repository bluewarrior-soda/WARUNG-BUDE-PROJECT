#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Dish
{
    char name[1000];
    char customer[1000];
    int price;
    int quantity;
    struct Dish *prev, *next;
} *head, *tail, *curr;
 
void clear_screen ()
{
    system("clear");
}

void display_current_time()
{
    time_t current = time(NULL);
    printf("%s", ctime(&current));
}

const char* detect_OS() 
{
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
}

void press_ENTER ()
{
    puts("Press enter to continue");
    getchar();
}

void push_head (char *name, int price, int quantity)
{
    struct Dish *temp = (Dish*)malloc(sizeof(struct Dish));
    if (!head)
    {
        head = tail = temp;
    }
    else
    {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
}

void add_dish () // 1
{
    struct Dish *new_dish = (Dish*)malloc(sizeof(struct Dish));

    while (true)
    {
        int uppercase = 0, numbers = 0;
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf("%s", new_dish->name); getchar();

        char name[1000];
        strcpy(name, new_dish->name);
        int name_length = strlen(name);
        for (int i = 0; i < name_length; i++)
        {
            if (name[i] >= 'A' && name[i] <= 'Z')
            {
                uppercase++;
            }
            else if (name[i] >= '0' && name[i] <= '9')
            {
                numbers++;
            }
        }

        if (uppercase == 0 && numbers == 0) break;
    }
    
    do
    {
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d", &new_dish->price); getchar();
    } while (new_dish->price < 1000 || new_dish->price > 50000);
    
    do
    {
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d", &new_dish->quantity);
    } while (new_dish->quantity < 1 || new_dish->quantity > 999);
    
    push_head(new_dish->name, new_dish->price, new_dish->quantity);
    puts("The dish has been added!");
    press_ENTER();
}

bool search_dish (char *target_dish)
{
    curr = head;
    while (curr)
    {
        if (strcmp(target_dish, curr->name) == 0)
        {
            return true;
        }
        curr = curr->next;
    }

    return false;
}

void remove_dish () // 2
{
    printf("Bude's Menu\n");
    printf("=========================================\n");
    printf("%-5s %-8s %-15s %-10s\n", "No.", "Name", "Quantity", "Price");
    // for (int i = 0; i++)
    // {
    //     printf("%-5s %-8s %-15s %-10s\n", i + 1, dish[i].name, dish[i].quantity, dish[i].price);
    // }
    printf("=========================================\n");

    char target_dish[1000];
    printf("Insert dish's name to be deleted: ");
    scanf("%s", target_dish); getchar();

    bool found = search_dish(target_dish);
    if (found == true)
    {
        // delete
    }
    else
    {
        puts("Dish not found!");
    }
}

void add_customer () // 3
{
    struct Dish *dish = (Dish*)malloc(sizeof(struct Dish));
    bool detected = false;
    do
    {
        printf("Insert the customer's name [Without space]: ");
        scanf("%[^\n]", dish->customer);

        char customer_name[1000];
        strcpy(customer_name, dish->customer);

        for (int i = 0; customer_name[i] != '\0'; i++)
        {
            if (customer_name[i] == ' ')
            {
                detected = true;
                break;
            }
        }
    } while (detected == true);
    

}

bool find_customer (char *target_customer)
{
    curr = head;
    while (curr)
    {
        if (strcmp(curr->customer, target_customer) == 0)
        {
            return true;
        }
        curr = curr->next;
    }

    return false;
}

void search_customer () // 4
{
    char target_customer[1000];
    printf("Insert the customer’s name to be searched: ");
    scanf("%s", target_customer);

    bool found = find_customer(target_customer);
    if (found == true)
    {

    }
    else
    {
        printf("%s is not present\n", target_customer);
    }
}

void view_warteg () // 5
{
    puts("Customer's List");
    curr = head;
    while (curr)
    {
        printf("%s\n", curr->customer);
        curr = curr->next;
    }
}

bool search_customer (char *customer_name)
{
    curr = head;
    while (curr)
    {
        if (strcmp(customer_name, curr->customer) == 0)
        {
            return true;
        }
        curr = curr->next;
    }

    return false;
}

int find_total_stocks ()
{
    int sum = 0;
    curr = head;
    while (curr)
    {
        sum = sum + curr->quantity;
        curr = curr->next;
    }

    return sum;
}

void order_dish () // 6
{
    struct Dish *dish = (Dish*)malloc(sizeof(struct Dish));
    printf("Insert the customer’s name: ");
    scanf("%s", dish->customer); getchar();
    char customer_name[1000];
    strcpy(customer_name, dish->customer);

    while (true)
    {
        if (search_customer(customer_name) == true)
        {
            break;
        }
        else
        {
            printf("Insert the customer’s name: ");
            scanf("%s", dish->customer); getchar();
            char customer_name[1000];
            strcpy(customer_name, dish->customer);
        }
    }

    int amount_of_dish;
    printf("Insert the amount of dish: ");
    scanf("%d", &amount_of_dish); getchar();
    int total_stocks = find_total_stocks();
    while (true)
    {
        if (amount_of_dish >= 1 && amount_of_dish <= total_stocks)
        {
            break;
        }
        else
        {
            printf("Insert the amount of dish: ");
            scanf("%d", &amount_of_dish); getchar();
            total_stocks = find_total_stocks();
        }
    }

    for (int i = 1; i <= amount_of_dish; i++)
    {
        printf("[%d] Insert the dish’s name and quantity: ", i);
        scanf("%[^\n]", dish->name);
        
    }
}

void payment () // 7
{
    
}

void exit_warteg () // 8
{
    puts("Please expand your terminal to full screen!");
    press_ENTER();

    FILE *splash = fopen("splash-screen.txt", "r");

    char s[10000];
    while (!feof(splash))
    {
        fscanf(splash, "%[^\n]\n", s);
        printf("%s\n", s);
    }

    fclose(splash);
}

void main_menu ()
{
    printf("System : %s\n", detect_OS());
    display_current_time();
    puts("1. Add Dish");
    puts("2. Remove Dish");
    puts("3. Add Customer");
    puts("4. Search Customer");
    puts("5. View Warteg");
    puts("6. Order");
    puts("7. Payment");
    puts("8. Exit Warteg");
    int option;
    do
    {
        printf(">> ");
        scanf("%d", &option);
    } while (option < 1 || option > 8);

    switch (option)
    {
        case 1: add_dish();
        break;
        case 2: remove_dish();
        break;
        case 3:
        break;
        case 4:
        break;
        case 5: 
        break;
        case 6: 
        break;
        case 7:
        break;
        default: exit_warteg();
        break;
    }
}

int main()
{
    main_menu();

    return 0;
}