#include "gtest/gtest.h"
#include "denizen.h"
#include "district.h"
#include "alarmed.h"
#include "zombie.h"
#include "ignorant.h"

int main(int argc, char** argv) { // needed to run tests
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}

TEST(alarmedTest, makeAlarmed) { // test making an alarmed
    Denizen* a = new Alarmed(1, 1);
    EXPECT_EQ(typeid(*a), typeid(Alarmed));
    EXPECT_EQ(a->getId(), 1);
    EXPECT_EQ(a->getDistrictId(), 1);
    EXPECT_EQ(a->getState(), Denizen::State::Alarmed);
    delete a;
};

TEST(ignorantTest, makeIgnorant) { // test making an alarmed
    Denizen* a = new Ignorant (1, 1);
    EXPECT_EQ(typeid(*a), typeid(Ignorant));
    EXPECT_EQ(a->getId(), 1);
    EXPECT_EQ(a->getDistrictId(), 1);
    EXPECT_EQ(a->getState(), Denizen::State::Ignorant);
    delete a;
};

TEST(zombieTest, makeZombie) { // test making an alarmed
    Denizen* a = new Zombie (1, 1);
    EXPECT_EQ(typeid(*a), typeid(Zombie));
    EXPECT_EQ(a->getId(), 1);
    EXPECT_EQ(a->getDistrictId(), 1);
    EXPECT_EQ(a->getState(), Denizen::State::Zombie);
    delete a;
};

TEST(districtTest, makeDistrict) { // test making a district
    District* a = new District (1, "district");
    EXPECT_EQ(typeid(*a), typeid(District));
    EXPECT_EQ(a->getId(), 1);
    EXPECT_EQ(a->getName(), "district1");
    delete a;
};

TEST(districtAddToOverall, addDenizens) { // test adding denizens to overall population in district
    District* a = new District (1);
    Ignorant* b = new Ignorant (1,1);
    Alarmed* c = new Alarmed (2,1);
    Zombie* d = new Zombie (3,1);
    a->addDenizen(b);
    a->addDenizen(c);
    a->addDenizen(d);
    EXPECT_EQ(typeid(*a->getDenizens(0)), typeid(Ignorant));
    EXPECT_EQ(typeid(*a->getDenizens(1)), typeid(Alarmed));
    EXPECT_EQ(typeid(*a->getDenizens(2)), typeid(Zombie));
    delete b;
    delete a;
    delete c;
    delete d;
}

TEST(districtAddToSub, addDenizens) { // test adding denizens to sub populations in district
    District* a = new District (1);
    Ignorant* b = new Ignorant (1,1);
    Alarmed* c = new Alarmed (2,1);
    Zombie* d = new Zombie (3,1);
    a->addDenizen(b);
    a->addDenizen(c);
    a->addDenizen(d);
    EXPECT_EQ((*a->getIgnorant(0)).getId(), 1);
    EXPECT_EQ((*a->getAlarmed(0)).getId(), 2);
    EXPECT_EQ((*a->getZombie(0)).getId(), 3);
    delete b;
    delete a;
    delete c;
    delete d;
}

TEST(changeIgToZom, changeDenizen) { // test changing denizen from Ignorant to Zombie
    District* a = new District (1);
    Ignorant* b = new Ignorant (1,1);
    a->addDenizen(b);
    a->createZombie(b);
    EXPECT_EQ(typeid(*a->getDenizens(0)), typeid(Zombie));
    EXPECT_EQ((a->getDenizens(0))->getId(), 1);
    EXPECT_EQ((a->getDenizens(0))->getDistrictId(), 1);
    EXPECT_EQ((a->getDenizens(0))->getState(), Denizen::State::Zombie);
    EXPECT_EQ(a->getAllPop(), 1);
    EXPECT_EQ(a->getIgnorantPop(), 0);
    EXPECT_EQ(a->getZombiePop(), 1);
    delete a->getDenizens(0);
    delete a;
}

TEST(changeAlToZom, changeDenizen) { // test changing denizen from Ignorant to Zombie
    District* a = new District (1);
    Alarmed* b = new Alarmed (1,1);
    a->addDenizen(b);
    a->createZombie(b);
    EXPECT_EQ(typeid(*a->getDenizens(0)), typeid(Zombie));
    EXPECT_EQ((a->getDenizens(0))->getId(), 1);
    EXPECT_EQ((a->getDenizens(0))->getDistrictId(), 1);
    EXPECT_EQ((a->getDenizens(0))->getState(), Denizen::State::Zombie);
    EXPECT_EQ(a->getAllPop(), 1);
    EXPECT_EQ(a->getAlarmedPop(), 0);
    EXPECT_EQ(a->getZombiePop(), 1);
    delete a->getDenizens(0);
    delete a;
}

TEST(changeIgToAl, changeDenizen) { // test changing denizen from Ignorant to Zombie
    District* a = new District (1);
    Ignorant* b = new Ignorant (1,1);
    a->addDenizen(b);
    a->createAlarmed(b);
    EXPECT_EQ(typeid(*a->getDenizens(0)), typeid(Alarmed));
    EXPECT_EQ((a->getDenizens(0))->getId(), 1);
    EXPECT_EQ((a->getDenizens(0))->getDistrictId(), 1);
    EXPECT_EQ((a->getDenizens(0))->getState(), Denizen::State::Alarmed);
    EXPECT_EQ(a->getAllPop(), 1);
    EXPECT_EQ(a->getIgnorantPop(), 0);
    EXPECT_EQ(a->getAlarmedPop(), 1);
    delete a->getDenizens(0);
    delete a;
}