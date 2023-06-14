# Coffee Shop
## Understanding the Problem

The goal is to make a coffe shop kiosk that both customers and employees can use.
Employees can use the kiosk to change the menu and prices, and to see the orders that have been placed, and revenue.

Customers can use the kiosk to place orders, and to see the menu and prices.
When viewing the menu you can search / sort by price, name, and category.
Everyone can view the menu, address, and phone number.

## Devising a 

```
Load menu from file
Load orders from file
Load revenue from file
```

```
If Employee
    1. View shop revenue:
        Print revenue

    2. View orders:
        Print orders

    3. Add an item to coffee menu:
        Ask for name
        Ask for price
        Ask for category
        Add item to menu
        Write to file

    4. Remove an item from coffee menu:
        Ask for name
        Remove item from menu
        Write to file

    5. View coffee menu:
        Print menu

    6. View address: 
        Print address

    7. View phone number:
        Print phone number
    
    8. Exit:
        Exit
```
```
If Customer
    1. View coffee menu:
        Print menu

    2. Search by price:
        Ask for price
        Print menu items with price less than or equal to input

    3. Search by coffee name:
        Ask for name
        Print menu items with name equal to input

    4. Place an order:
        Ask for name
        Ask for quantity
        Add order to orders
        Write to file

    5. View address:
        Print address

    6. View phone:
        Print phone number

    7. Exit:
        Exit

```

## Testing the Program

<!-- A bunch of test cases for the program including what the expected result should be -->
| Login Input | Expected Result |
|-----------|-----------------|
| User Input: Employee / E | Employee Options |
| User Input: Customer / C | Customer Options |
| --- Invalid Input ---||
| Login Input: 9 | Invalid Input / Ask for new input |
| Login Input: A | Invalid Input / Ask for new input |
| Login Input: Mr Boss Man | Invalid Input / Ask for new input |

| Employee Input | Expected Result |
|-----------|-----------------|
| User Input: 1 | Print revenue |
| User Input: 2 | Print orders |
| User Input: 3 | Ask for name, price, category, add item to menu |
| User Input: 4 | Ask for name, remove item from menu |
| User Input: 5 | Print menu |
| User Input: 6 | Print address |
| User Input: 7 | Print phone number |
| User Input: 8 | Exit |
| --- Invalid Input ---||
| User Input: 9 | Invalid Input / Ask for new input |
| User Input: 0 | Invalid Input / Ask for new input |
| User Input: -1 | Invalid Input / Ask for new input |

| Customer Input | Expected Result |
|-----------|-----------------|
| User Input: 1 | Print menu |
| User Input: 2 | Ask for price and print menu items with price less than or equal to input
| User Input: 3 | Ask for name and print menu items with name equal to input |
| User Input: 4 | Ask for name and quantity and add order to orders |
| User Input: 5 | Print address |
| User Input: 6 | Print phone number |
| User Input: 7 | Exit |
| --- Invalid Input ---||
| User Input: 9 | Invalid Input / Ask for new input |
| User Input: 0 | Invalid Input / Ask for new input |
| User Input: -1 | Invalid Input / Ask for new input |
| Place Order: Item not in menu | Invalid Input / Ask for new input |
| Place Order: Quantity not a number | Invalid Input / Ask for new input |
| Place Order: Quantity less than 1 | Invalid Input / Ask for new input |

table {
    width:100%;
}