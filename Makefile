# ============================================================
# Makefile - Zombie Survival Game
# Biên dịch mã nguồn trong app/ (ứng dụng) có sử dụng lib/ (thư viện)
# ============================================================

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

LIB_DIR  := lib
APP_DIR  := app
INCLUDES := -I$(LIB_DIR) -I$(APP_DIR)

TARGET   := game
SRCS     := $(wildcard $(APP_DIR)/*.cpp)
OBJS     := $(SRCS:.cpp=.o)

# Mặc định: biên dịch toàn bộ dự án
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Biên dịch từng file .cpp trong app/ thành .o, có include lib/ và app/
$(APP_DIR)/%.o: $(APP_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Biên dịch và chạy luôn chương trình
run: all
	./$(TARGET)

# Xóa file biên dịch trung gian và file thực thi
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
