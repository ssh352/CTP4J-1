package cn.yiwang.ctp.struct;

/**
 * 深度行情
 * 
 * @author Wang
 * @version 1.0
 */
public class CTPDepthMarketData extends CTPField {
    /** 交易日 char[9] */
    public String TradingDay;
    /** 合约代码 char[31] */
    public String InstrumentID;
    /** 交易所代码 char[9] */
    public String ExchangeID;
    /** 合约在交易所的代码 char[31] */
    public String ExchangeInstID;
    /** 最新价 */
    public float LastPrice;
    /** 上次结算价 */
    public float PreSettlementPrice;
    /** 昨收盘 */
    public float PreClosePrice;
    /** 昨持仓量 */
    public float PreOpenInterest;
    /** 今开盘 */
    public float OpenPrice;
    /** 最高价 */
    public float HighestPrice;
    /** 最低价 */
    public float LowestPrice;
    /** 数量 */
    public int Volume;
    /** 成交金额 */
    public float Turnover;
    /** 持仓量 */
    public float OpenInterest;
    /** 今收盘 */
    public float ClosePrice;
    /** 本次结算价 */
    public float SettlementPrice;
    /** 涨停板价 */
    public float UpperLimitPrice;
    /** 跌停板价 */
    public float LowerLimitPrice;
    /** 昨虚实度 */
    public float PreDelta;
    /** 今虚实度 */
    public float CurrDelta;
    /** 最后修改时间 [9] */
    public String UpdateTime;
    /** 最后修改毫秒 */
    public int UpdateMillisec;
    /** 申买价一 */
    public float BidPrice1;
    /** 申买量一 */
    public int BidVolume1;
    /** 申卖价一 */
    public float AskPrice1;
    /** 申卖量一 */
    public int AskVolume1;
    /** 申买价二 */
    public float BidPrice2;
    /** 申买量二 */
    public int BidVolume2;
    /** 申卖价二 */
    public float AskPrice2;
    /** 申卖量二 */
    public int AskVolume2;
    /** 申买价三 */
    public float BidPrice3;
    /** 申买量三 */
    public int BidVolume3;
    /** 申卖价三 */
    public float AskPrice3;
    /** 申卖量三 */
    public int AskVolume3;
    /** 申买价四 */
    public float BidPrice4;
    /** 申买量四 */
    public int BidVolume4;
    /** 申卖价四 */
    public float AskPrice4;
    /** 申卖量四 */
    public int AskVolume4;
    /** 申买价五 */
    public float BidPrice5;
    /** 申买量五 */
    public int BidVolume5;
    /** 申卖价五 */
    public float AskPrice5;
    /** 申卖量五 */
    public int AskVolume5;
    /** 当日均价 */
    public float AveragePrice;
    /** 业务日期 char[9] */
    public String ActionDay;

    public String toString() {
        StringBuffer sb = new StringBuffer();
        sb.append(getString(TradingDay));
        sb.append(",");
        sb.append(getString(InstrumentID));
        sb.append(",");
        sb.append(getString(ExchangeID));
        sb.append(",");
        sb.append(getString(ExchangeInstID));
        sb.append(",");
        sb.append(LastPrice);
        sb.append(",");
        sb.append(PreSettlementPrice);
        sb.append(",");
        sb.append(PreClosePrice);
        sb.append(",");
        sb.append(PreOpenInterest);
        sb.append(",");
        sb.append(OpenPrice);
        sb.append(",");
        sb.append(HighestPrice);
        sb.append(",");
        sb.append(LowestPrice);
        sb.append(",");
        sb.append(Volume);
        sb.append(",");
        sb.append(Turnover);
        sb.append(",");
        sb.append(OpenInterest);
        sb.append(",");
        sb.append(ClosePrice);
        sb.append(",");
        sb.append(SettlementPrice);
        sb.append(",");
        sb.append(UpperLimitPrice);
        sb.append(",");
        sb.append(LowerLimitPrice);
        sb.append(",");
        sb.append(PreDelta);
        sb.append(",");
        sb.append(CurrDelta);
        sb.append(",");
        sb.append(getString(UpdateTime));
        sb.append(",");
        sb.append(UpdateMillisec);
        sb.append(",");
        sb.append(BidPrice1);
        sb.append(",");
        sb.append(BidVolume1);
        sb.append(",");
        sb.append(AskPrice1);
        sb.append(",");
        sb.append(AskVolume1);
        sb.append(",");
        sb.append(BidPrice2);
        sb.append(",");
        sb.append(BidVolume2);
        sb.append(",");
        sb.append(AskPrice2);
        sb.append(",");
        sb.append(AskVolume2);
        sb.append(",");
        sb.append(BidPrice3);
        sb.append(",");
        sb.append(BidVolume3);
        sb.append(",");
        sb.append(AskPrice3);
        sb.append(",");
        sb.append(AskVolume3);
        sb.append(",");
        sb.append(BidPrice4);
        sb.append(",");
        sb.append(BidVolume4);
        sb.append(",");
        sb.append(AskPrice4);
        sb.append(",");
        sb.append(AskVolume4);
        sb.append(",");
        sb.append(BidPrice5);
        sb.append(",");
        sb.append(BidVolume5);
        sb.append(",");
        sb.append(AskPrice5);
        sb.append(",");
        sb.append(AskVolume5);
        sb.append(",");
        sb.append(AveragePrice);
        sb.append(",");
        sb.append(getString(ActionDay));
        return sb.toString();
    }
}
