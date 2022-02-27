/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part5-2. 探索、線形探索のテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/C05_2_ALDS1_4_A_linear_search.h"

namespace ALDS1_4_A {

class Test_ALDS1_4_A : public ::testing::Test {
 protected:
  LinearSearch* linear_search_;
  virtual void SetUp() { linear_search_ = new LinearSearch(); }
  virtual void TearDown() { delete linear_search_; }
};

TEST_F(Test_ALDS1_4_A, SearchTarget_1) {
  ASSERT_ANY_THROW(linear_search_->TargetIsIncludedInSource(0));
  ASSERT_EQ(0, linear_search_->SearchTarget());
}

TEST_F(Test_ALDS1_4_A, SearchTarget_2) {
  linear_search_->AddOneTarget(10);
  linear_search_->AddOneTarget(1);
  linear_search_->AddOneTarget(400);
  linear_search_->AddOneTarget(77);

  linear_search_->AddOneSource(10);
  linear_search_->AddOneSource(9);
  linear_search_->AddOneSource(7);
  linear_search_->AddOneSource(8);
  linear_search_->AddOneSource(1);
  linear_search_->AddOneSource(6);
  linear_search_->AddOneSource(5);
  linear_search_->AddOneSource(4);
  linear_search_->AddOneSource(3);
  linear_search_->AddOneSource(2);
  linear_search_->AddOneSource(1);
  linear_search_->AddOneSource(0);

  ASSERT_TRUE(linear_search_->TargetIsIncludedInSource(0));
  ASSERT_TRUE(linear_search_->TargetIsIncludedInSource(1));
  ASSERT_FALSE(linear_search_->TargetIsIncludedInSource(2));
  ASSERT_FALSE(linear_search_->TargetIsIncludedInSource(3));
  ASSERT_EQ(2, linear_search_->SearchTarget());
}

TEST_F(Test_ALDS1_4_A, SearchTarget_3) {
  linear_search_->AddOneTarget(3);
  linear_search_->AddOneTarget(4);
  linear_search_->AddOneTarget(1);

  linear_search_->AddOneSource(1);
  linear_search_->AddOneSource(2);
  linear_search_->AddOneSource(3);
  linear_search_->AddOneSource(4);
  linear_search_->AddOneSource(5);

  ASSERT_EQ(3, linear_search_->SearchTarget());
}

TEST_F(Test_ALDS1_4_A, CallLinearSearch_1) {
  std::ostringstream answer;
  answer << "3" << std::endl;

  std::ostringstream input_stream;
  input_stream << "5" << std::endl;
  input_stream << "1 2 3 4 5" << std::endl;
  input_stream << "3" << std::endl;
  input_stream << "3 4 1" << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallLinearSearch(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_4_A, CallLinearSearch_2) {
  std::ostringstream answer;
  answer << "14" << std::endl;

  std::ostringstream input_stream;
  input_stream << "500" << std::endl;
  input_stream << "0 933 743 262 529 700 508 752 256 256 119 711 351 843 705 108 393 330 366 169 932 917 847"
                  " 972 868 980 223 549 592 164 169 551 427 190 624 635 920 944 310 862 484 363 301 710 236"
                  " 876 431 929 397 675 491 190 344 134 425 629 30 727 126 743 334 104 760 749 620 256 932"
                  " 572 613 490 509 119 405 695 49 327 719 497 824 596 649 356 184 93 245 7 306 509 754 352"
                  " 665 783 738 801 690 330 337 195 656 963 11 427 42 106 968 212 1 510 480 658 571 331 814"
                  " 847 564 197 625 438 931 18 487 151 187 913 179 995 750 750 913 562 134 273 547 521 830 140"
                  " 557 678 726 503 597 408 893 988 238 85 93 188 720 211 746 387 710 209 887 668 103 473 900"
                  " 674 105 183 952 370 787 302 410 905 110 400 996 142 585 860 47 924 731 158 386 219 400 415"
                  " 55 682 874 61 6 602 268 365 470 518 723 89 106 319 130 655 732 993 974 595 810 673 55 730 95"
                  " 245 705 694 948 873 353 474 760 741 756 644 143 640 737 679 135 149 529 210 607 417 255 787"
                  " 373 626 445 112 172 595 153 53 183 717 655 17 176 77 776 399 654 728 2 161 455 870 316 694"
                  " 381 930 480 604 386 359 207 954 79 702 365 453 732 836 432 563 17 107 583 910 467 116 546"
                  " 719 528 71 107 256 520 353 528 154 430 477 48 520 204 414 810 719 925 298 131 701 709 751"
                  " 22 817 652 924 695 471 153 625 978 616 142 597 88 732 917 404 743 395 749 407 936 302 767"
                  " 45 563 340 398 896 51 807 767 997 978 650 809 330 360 716 161 293 209 753 98 130 634 543"
                  " 889 88 31 692 401 674 294 693 165 949 765 737 458 841 48 943 229 215 389 209 388 754 243"
                  " 501 271 516 564 277 912 5 611 212 782 92 123 201 324 4 437 602 804 363 391 273 575 906 759"
                  " 626 896 859 763 358 577 484 747 156 948 605 454 194 359 430 323 883 24 447 202 847 876 49"
                  " 792 588 304 133 558 842 414 567 728 506 391 0 992 118 398 718 868 975 579 119 363 596 379"
                  " 916 466 840 232 430 414 155 571 311 179 796 300 216 903 993 55 728 481 905 29 37 897 286 657"
                  " 377 682 554 506 757 529 580 641 866 852 933 660 490 616 732 606 114 185 647 227 435 58 183 110"
                  " 742 374 604 671 872 605 480 671 979 717 481 680 791"
               << std::endl;
  input_stream << "30" << std::endl;
  input_stream << "0 9 18 30 31 42 48 49 59 74"
                  " 85 115 121 153 165 168 181 195 205 207"
                  " 220 228 248 252 255 270 274 289 291 300"
               << std::endl;
  std::istringstream iss(input_stream.str());
  testing::internal::CaptureStdout();
  CallLinearSearch(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_4_A
