INSERT INTO Products (Name, SellingPrice)
VALUES('Laptop', 15000);

INSERT INTO PhysicalProducts(ProductID, StorageCost, StockQuantity)
VALUES(1, 200, 50);

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(1, 'Processor', 5000, 'variable');

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(1, 'RAM', 1500, 'variable');

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(1, 'Packaging', 100, 'variable');

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(1, 'Design Cost', 2000, 'fixed');

INSERT INTO SaleTransactions(ProductID, Quantity, SalePrice, SaleMonth, SaleYear)
VALUES(1, 20, 15000, 1, 2025);

INSERT INTO MonthlyFixedCosts(Description, Amount, CostMonth, CostYear)
VALUES('Factory Rent', 20000, 1, 2025);

INSERT INTO MonthlyFixedCosts(Description, Amount, CostMonth, CostYear)
VALUES('Manager Salary', 15000, 1, 2025);

INSERT INTO MonthlyFixedCosts(Description, Amount, CostMonth, CostYear)
VALUES('Internet', 1000, 1, 2025);

INSERT INTO Products (Name, SellingPrice)
VALUES('Mouse', 300);

INSERT INTO PhysicalProducts(ProductID, StorageCost, StockQuantity)
VALUES(2, 10, 200);

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(2, 'Plastic', 60, 'variable');

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(2, 'Sensor', 50, 'variable');

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(2, 'Packaging', 10, 'variable');

INSERT INTO SaleTransactions(ProductID, Quantity, SalePrice, SaleMonth, SaleYear)
VALUES(2, 120, 300, 1, 2025);

INSERT INTO Products (Name, SellingPrice)
VALUES('Keyboard', 600);

INSERT INTO PhysicalProducts(ProductID, StorageCost, StockQuantity)
VALUES(3, 20, 150);

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(3, 'Keys', 120, 'variable');

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(3, 'Circuit Board', 150, 'variable');

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(3, 'Packaging', 20, 'variable');

INSERT INTO SaleTransactions(ProductID, Quantity, SalePrice, SaleMonth, SaleYear)
VALUES(3, 80, 600, 1, 2025);

INSERT INTO Products (Name, SellingPrice)
VALUES('Monitor', 4000);

INSERT INTO PhysicalProducts(ProductID, StorageCost, StockQuantity)
VALUES(4, 70, 40);

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(4, 'Screen', 1800, 'variable');

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(4, 'Stand', 250, 'variable');

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(4, 'Packaging', 80, 'variable');

INSERT INTO SaleTransactions(ProductID, Quantity, SalePrice, SaleMonth, SaleYear)
VALUES(4, 25, 4000, 1, 2025);

INSERT INTO Products (Name, SellingPrice)
VALUES('Computer Maintenance', 800);

INSERT INTO ServiceOfferings(ProductID, HourlyLaborRate,HoursPerUnit)
VALUES(5,200,3);

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(5, 'Technician Wage', 250, 'variable');

INSERT INTO CostComponents(ProductID, Name, Amount, Type)
VALUES(5, 'Transportation', 50, 'variable');

INSERT INTO SaleTransactions(ProductID, Quantity, SalePrice, SaleMonth, SaleYear)
VALUES(5, 30, 800, 1, 2025);

INSERT INTO SaleTransactions(ProductID, Quantity, SalePrice, SaleMonth, SaleYear)
VALUES(1, 15, 15000, 2, 2025);

INSERT INTO SaleTransactions(ProductID, Quantity, SalePrice, SaleMonth, SaleYear)
VALUES(1, 22, 15000, 3, 2025);

INSERT INTO SaleTransactions(ProductID, Quantity, SalePrice, SaleMonth, SaleYear)
VALUES(1, 18, 15000, 4, 2025);

INSERT INTO SaleTransactions(ProductID, Quantity, SalePrice, SaleMonth, SaleYear)
VALUES(2, 140, 300, 2, 2025);

INSERT INTO SaleTransactions(ProductID, Quantity, SalePrice, SaleMonth, SaleYear)
VALUES(2, 160, 300, 3, 2025);

INSERT INTO SaleTransactions(ProductID, Quantity, SalePrice, SaleMonth, SaleYear)
VALUES(2, 110, 300, 4, 2025);

INSERT INTO MonthlyFixedCosts(Description, Amount, CostMonth, CostYear)
VALUES('Factory Rent', 20000, 2, 2025);

INSERT INTO MonthlyFixedCosts(Description, Amount, CostMonth, CostYear)
VALUES('Manager Salary', 15000, 2, 2025);

INSERT INTO MonthlyFixedCosts(Description, Amount, CostMonth, CostYear)
VALUES('Internet', 1000, 2, 2025);

INSERT INTO MonthlyFixedCosts(Description, Amount, CostMonth, CostYear)
VALUES('Factory Rent', 20000, 3, 2025);

INSERT INTO MonthlyFixedCosts(Description, Amount, CostMonth, CostYear)
VALUES('Manager Salary', 15000, 3, 2025);

INSERT INTO MonthlyFixedCosts(Description, Amount, CostMonth, CostYear)
VALUES('Internet', 1000, 3, 2025);