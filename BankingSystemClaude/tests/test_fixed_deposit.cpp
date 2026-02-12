#include <gtest/gtest.h>
#include "FixedDeposit.h"

class FixedDepositTest : public ::testing::Test {
protected:
    void SetUp() override {
        fd12Months = std::make_shared<FixedDeposit>(10000.0, 12);
        fd24Months = std::make_shared<FixedDeposit>(10000.0, 24);
    }

    void TearDown() override {
        fd12Months.reset();
        fd24Months.reset();
    }

    std::shared_ptr<FixedDeposit> fd12Months;
    std::shared_ptr<FixedDeposit> fd24Months;
};

// Test FD creation with 12 months
TEST_F(FixedDepositTest, CreateFD12Months) {
    EXPECT_DOUBLE_EQ(fd12Months->getPrincipal(), 10000.0);
    EXPECT_EQ(fd12Months->getTenure(), 12);
    EXPECT_DOUBLE_EQ(fd12Months->getInterestRate(), 6.5);
}

// Test FD creation with 24 months
TEST_F(FixedDepositTest, CreateFD24Months) {
    EXPECT_DOUBLE_EQ(fd24Months->getPrincipal(), 10000.0);
    EXPECT_EQ(fd24Months->getTenure(), 24);
    EXPECT_DOUBLE_EQ(fd24Months->getInterestRate(), 7.5);
}

// Test maturity amount calculation for 12 months
TEST_F(FixedDepositTest, MaturityAmount12Months) {
    // 10000 * (1 + (6.5/100 * 1)) = 10000 * 1.065 = 10650
    double expectedMaturity = 10650.0;
    EXPECT_NEAR(fd12Months->calculateMaturityAmount(), expectedMaturity, 0.01);
}

// Test maturity amount calculation for 24 months
TEST_F(FixedDepositTest, MaturityAmount24Months) {
    // 10000 * (1 + (7.5/100 * 2)) = 10000 * 1.15 = 11500
    double expectedMaturity = 11500.0;
    EXPECT_NEAR(fd24Months->calculateMaturityAmount(), expectedMaturity, 0.01);
}

// Test FD with invalid tenure
TEST(FixedDepositCreationTest, InvalidTenure) {
    EXPECT_THROW({
        FixedDeposit fd(10000.0, 6);
    }, std::invalid_argument);
    
    EXPECT_THROW({
        FixedDeposit fd(10000.0, 36);
    }, std::invalid_argument);
}

// Test FD with negative amount
TEST(FixedDepositCreationTest, NegativeAmount) {
    EXPECT_THROW({
        FixedDeposit fd(-5000.0, 12);
    }, std::invalid_argument);
}

// Test FD with zero amount
TEST(FixedDepositCreationTest, ZeroAmount) {
    EXPECT_THROW({
        FixedDeposit fd(0.0, 12);
    }, std::invalid_argument);
}

// Test maturity date calculation
TEST_F(FixedDepositTest, MaturityDateFormat) {
    std::string maturityDate = fd12Months->getMaturityDate();
    // Check if date is in correct format (YYYY-MM-DD)
    EXPECT_EQ(maturityDate.length(), 10);
    EXPECT_EQ(maturityDate[4], '-');
    EXPECT_EQ(maturityDate[7], '-');
}

// Test different principal amounts
TEST(FixedDepositCalculationTest, DifferentPrincipals) {
    FixedDeposit fd1(5000.0, 12);
    FixedDeposit fd2(20000.0, 12);
    FixedDeposit fd3(50000.0, 24);
    
    EXPECT_NEAR(fd1.calculateMaturityAmount(), 5325.0, 0.01);
    EXPECT_NEAR(fd2.calculateMaturityAmount(), 21300.0, 0.01);
    EXPECT_NEAR(fd3.calculateMaturityAmount(), 57500.0, 0.01);
}

// Test serialization and deserialization
TEST_F(FixedDepositTest, SerializationDeserialization) {
    std::string serialized = fd12Months->serialize();
    FixedDeposit deserialized = FixedDeposit::deserialize(serialized);
    
    EXPECT_DOUBLE_EQ(deserialized.getPrincipal(), fd12Months->getPrincipal());
    EXPECT_EQ(deserialized.getTenure(), fd12Months->getTenure());
    EXPECT_DOUBLE_EQ(deserialized.getInterestRate(), fd12Months->getInterestRate());
}

// Test interest calculation accuracy
TEST(FixedDepositInterestTest, InterestCalculation) {
    FixedDeposit fd(10000.0, 12);
    double maturity = fd.calculateMaturityAmount();
    double interest = maturity - 10000.0;
    
    // Interest should be 10000 * 6.5% = 650
    EXPECT_NEAR(interest, 650.0, 0.01);
}

// Test large amount FD
TEST(FixedDepositCreationTest, LargeAmount) {
    FixedDeposit fd(1000000.0, 24); // 10 Lakh
    EXPECT_DOUBLE_EQ(fd.getPrincipal(), 1000000.0);
    EXPECT_NEAR(fd.calculateMaturityAmount(), 1150000.0, 0.01);
}

// Test small amount FD
TEST(FixedDepositCreationTest, SmallAmount) {
    FixedDeposit fd(100.0, 12);
    EXPECT_DOUBLE_EQ(fd.getPrincipal(), 100.0);
    EXPECT_NEAR(fd.calculateMaturityAmount(), 106.5, 0.01);
}
