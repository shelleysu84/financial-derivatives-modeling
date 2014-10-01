class Option : public Instrument {
	public :
		enum Exercise {European = 'E', American = 'A'};
		enum Type { Call = 'C', Put = 'P'};
		
		Option() {}
		Option(double price, double strike, double vol, double rate, double vol, double dic, double T, char type, char exercise);
		
		virtual ~option() {}
		Option(const Handle<PricingEngine>& engine);
	
  
};
