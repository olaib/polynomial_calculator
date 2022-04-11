#pragma once
struct Location
{
	Location(size_t row, size_t col) : m_row(row), m_col(col) {};
	size_t m_row;
	size_t m_col;
	bool isSameLocation(Location other)const {
		return(m_row == other.m_row && m_col == other.m_col);
	}
};