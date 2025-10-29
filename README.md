[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/pAwGQi_N)

# PA4 Skeleton Code
We expect a fully functioninig command line REPL application for an inventory querying system. Feel free to modify the skeleton code as you see fit.

### How to run the current skeleton code
`make` will compile and execute the skeleton code

Feel free to modify Makefile as you see fit.

# My Design Choices
### Data Structure Choice
 1. I decided to use a hash table with seperate chaining as the primary data structure for this project. I used the same template to perform both item lookups by uniqID as well as listInventory lookups for all items in a given category. 
 2. I instantiate two objects, one using the uniqIds as keys for lookups, and one using the categories as keys, creating long lists at each index of the hash table storing all items matching that category. Since we need to print every single one, I think this is faster than open addressing because we just have to iterate through the list.

### CSV Parsing Choices
 1. I made all empty fields store as NA in their respective field in the Product class.
 2. All NA categories were skipped when I stored to my inventory table, as I dont see those as useful to a customer
 3. To deal with commas inside of fields that werent meant to be comma separated, I found that all fields containing those were surrounded with quotations. I implemented logic to detect when inside of quotes, and ignore commas for delimiting in those instances.
 4. To deal with category delimiting, I first store all categories in a single entry into one string with the rest of the data, then delimit it seperately by '|' construct Product objects with a vector of categories.

 ### Testing
 1. `test_csv_parse` runs the full CSV ingestion pipeline against the sample data to confirm known IDs and categories load correctly while invalid lookups return false.
 2. `test_hash_table` builds a small table and verifies successful lookups for existing products and failures for missing keys using the original Product fixtures.
 3. `test_hash_insert_overwrite` checks that inserting the same key twice overwrites the stored product and that the most recent details surface in `find`.
 4. `test_listByCategory_multiple_hits` inserts two products under the same category and asserts that both names are printed, guarding against accidental overwrites.
 5. `test_parseCSVLine_quotes` feeds a crafted CSV line with embedded quotes and empty fields to verify tokenization, quote unescaping, and NA substitution.
 6. `test_validCommand_variations` exercises the REPL command validator with valid and invalid inputs to ensure only supported commands pass through.
 7. `test_evalCommand_listInventory_output` invokes the REPL category listing to ensure the expected header and every matching product name are emitted.
