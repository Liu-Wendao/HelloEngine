#pragma once

namespace HelloEngine
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			:m_Time(time)
		{

		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; } //√Î
		float GetMilliseconds() const { return m_Time * 1000; } //∫¡√Î
	private:
		float m_Time;
	};
}