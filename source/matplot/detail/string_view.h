#pragma once
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace matplot {

class string_view {
private:
    const char* m_data;
    size_t m_size;

public:
    typedef char value_type;
    // 构造函数
    string_view() noexcept : m_data(nullptr), m_size(0) {}
    
    string_view(const char* str) : m_data(str), m_size(str ? strlen(str) : 0) {}
    
    string_view(const char* str, size_t len) : m_data(str), m_size(len) {}
    
    template <size_t N>
    string_view(const char (&str)[N]) noexcept : m_data(str), m_size(N - 1) {}

    string_view(const std::string& str) noexcept : m_data(str.data()), m_size(str.size()) {}

    // 基本访问器
    const char* data() const noexcept { return m_data; }
    size_t size() const noexcept { return m_size; }
    size_t length() const noexcept { return m_size; }
    bool empty() const noexcept { return m_size == 0; }

    // 元素访问
    const char& operator[](size_t pos) const noexcept {
        return m_data[pos];
    }

    const char& at(size_t pos) const {
        if (pos >= m_size) throw std::out_of_range("string_view::at");
        return m_data[pos];
    }

    const char& front() const noexcept { return m_data[0]; }
    const char& back() const noexcept { return m_data[m_size - 1]; }

    // 子串操作
    string_view substr(size_t pos = 0, size_t count = npos) const {
        if (pos > m_size) throw std::out_of_range("string_view::substr");
        size_t rlen = std::min(count, m_size - pos);
        return string_view(m_data + pos, rlen);
    }

    // 移除前缀和后缀
    void remove_prefix(size_t n) noexcept {
        m_data += n;
        m_size -= n;
    }

    void remove_suffix(size_t n) noexcept {
        m_size -= n;
    }

    // 比较操作符
    bool operator==(const string_view& other) const noexcept {
        if (m_size != other.m_size) return false;
        return memcmp(m_data, other.m_data, m_size) == 0;
    }

    bool operator!=(const string_view& other) const noexcept {
        return !(*this == other);
    }

    // 转换为字符串
    std::string to_string() const {
        return std::string(m_data, m_size);
    }

    // 查找操作
    size_t find(char c, size_t pos = 0) const noexcept {
        for (size_t i = pos; i < m_size; ++i) {
            if (m_data[i] == c) return i;
        }
        return npos;
    }

    size_t find(string_view str, size_t pos = 0) const noexcept {
        if (str.empty()) return pos <= m_size ? pos : npos;
        if (str.m_size > m_size || pos > m_size - str.m_size) return npos;
        
        // 简单的暴力匹配算法
        for (size_t i = pos; i <= m_size - str.m_size; ++i) {
            bool found = true;
            for (size_t j = 0; j < str.m_size; ++j) {
                if (m_data[i + j] != str.m_data[j]) {
                    found = false;
                    break;
                }
            }
            if (found) return i;
        }
        
        return npos;
    }

    size_t find_first_not_of(string_view str, size_t pos = 0) const noexcept {
        if (pos >= m_size) return npos;
        
        for (size_t i = pos; i < m_size; ++i) {
            bool found = false;
            // 检查当前字符是否在目标字符串中
            for (size_t j = 0; j < str.m_size; ++j) {
                if (m_data[i] == str.m_data[j]) {
                    found = true;
                    break;
                }
            }
            // 如果当前字符不在目标字符串中，返回位置
            if (!found) return i;
        }
        
        return npos;
    }
    size_t find_first_of(string_view str, size_t pos = 0) const noexcept {
        if (pos >= m_size || str.empty()) return npos;
        
        for (size_t i = pos; i < m_size; ++i) {
            // 检查当前字符是否在目标字符串中
            for (size_t j = 0; j < str.m_size; ++j) {
                if (m_data[i] == str.m_data[j]) {
                    return i;  // 找到匹配，返回位置
                }
            }
        }
        
        return npos;
    }
    static const size_t npos = -1;

    // 迭代器支持（简单版）
    const char* begin() const noexcept { return m_data; }
    const char* end() const noexcept { return m_data + m_size; }
    const char* cbegin() const noexcept { return m_data; }
    const char* cend() const noexcept { return m_data + m_size; }

    operator std::string() const {
        return to_string();
    }
};

// 输出流支持
inline std::ostream& operator<<(std::ostream& os, const string_view& sv) {
    return os.write(sv.data(), sv.size());
}

}