
#pragma once

namespace fw {

	class FWCore;

	class GameCore
	{
	public:
		GameCore(FWCore* m_pFW);

		virtual void Update() = 0;
		virtual void Draw() = 0;

		virtual ~GameCore();

	private:

	protected:
		FWCore* m_pFW = nullptr;
	};

	

} // namespace fw
