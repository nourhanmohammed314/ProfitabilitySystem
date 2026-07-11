create database Profitability_System;
use Profitability_System;
Create table Products(
	ProductID int identity(1,1) primary key,
	Name nvarchar(100) not null unique,
	SellingPrice Decimal(10,2) Not Null,
	constraint CK_Product_Name
	check (len(Name)>0),
	Constraint CK_Product_SellingPrice
	check(SellingPrice>=0)
	);
Create table PhysicalProducts(
	ProductID int primary key,
	StorageCost decimal(10,2) Not null,
	StockQuantity int not null,
	constraint CK_Physical_StorageCost
	check(StorageCost>=0),
	constraint CK_Physical_StockQuantity
	check(StockQuantity>=0),
	constraint Fk_Physical_Product
	foreign key(ProductID)
	References Products(ProductID)
	on delete cascade
);
Create table ServiceOfferings(
	ProductID int Primary key,
	HoursPerUnit int Not null,
	HourlyLaborRate Decimal(10,2) not null,
	constraint CK_Service_Hours
	check(HoursPerUnit>0),
	constraint CK_Service_LaborRate
	check(HourlyLaborRate>=0),
	constraint FK_Service_Product
	foreign key(ProductID)
	references Products(ProductID)
	on delete cascade
);
create table CostComponents(
	CostID int identity(1,1) primary key,
	ProductID int not null,
	Name nvarchar(100) not null,
	Amount Decimal(10,2) not null,
	Type nVarChar(10) not Null,
	constraint CK_Cost_Name
	check (len(Name)>0),
	constraint CK_Cost_Amount
	check(Amount>=0),
	constraint CK_Cost_Type
	check(Type in('variable','fixed')),
	constraint FK_Cost_Product
	foreign key(ProductID)
	references Products(ProductID)
	on delete cascade
);
create table SaleTransactions(
	SaleID int identity(1,1) primary key,
	ProductID int not null,
	Quantity int not null,
	SalePrice decimal(10,2) not null,
	SaleMonth tinyint not null,
	SaleYear smallint not null,
	constraint CK_Sale_Quantity
	check(Quantity>0),
	constraint CK_Sale_Price
	check(SalePrice>=0),
	constraint CK_Sale_Month
	check(SaleMonth between 1 and 12),
	constraint CK_Sale_Year
	check(SaleYear >=2000),
	constraint FK_Sale_Product
	foreign key(ProductID)
	references Products(ProductID)
	on delete cascade
);
create table MonthlyFixedCosts(
	FixedCostID int identity(1,1) primary key,
	Description nvarchar(255) not null,
	Amount decimal(10,2) not null,
	CostMonth tinyint not null,
	CostYear smallint not null,
	constraint CK_FixedCost_Description
	check (len(Description)>0),
	constraint CK_FixedCost_Amount
	check(Amount>=0),
	constraint CK_FixedCost_Month
	check(CostMonth between 1 and 12),
	constraint CK_FixedCost_Year
	check(CostYear>=2000)
);